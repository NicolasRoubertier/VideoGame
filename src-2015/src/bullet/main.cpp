// Sylvain.Lefebvre@inria.fr  2012-05-28
// ------------------------------------------------------------------

// Bullet documentation: http://bulletphysics.com/Bullet/BulletFull/

#include "../common/common.h"

#include <btBulletDynamicsCommon.h>

LIBSL_WIN32_FIX;

// ------------------------------------------------------------------

#include "shd.h"
AutoBindShader::shd *g_Sh = NULL;

// ------------------------------------------------------------------

// Constants
const int   c_ScreenW      = 800;
const int   c_ScreenH      = 600;

typedef struct {
  btBroadphaseInterface               *broadphase;
  btDefaultCollisionConfiguration     *collisionConfiguration;
  btCollisionDispatcher               *dispatcher;
  btSequentialImpulseConstraintSolver *solver;
  btDiscreteDynamicsWorld             *dynamicsWorld;
  time_t                               last;
} t_PhysicsEngine;

t_PhysicsEngine            g_Physics;

VertexBuffer              *g_Box = NULL;
std::vector<btRigidBody*>  g_Boxes;

TriangleMesh              *g_Scene = NULL;

// ------------------------------------------------------------------

// 'mainKeyPressed' is called everytime a key is pressed
void mainKeyPressed(uchar key)
{
  if (key == ' ') {
    // add a box in engine
    // -> size
      btVector3         exts = btVector3(0.5f,0.5f,0.5f);
      // -> shape
      btCollisionShape* box  = new btBoxShape(exts);
      // -> motion state
      btDefaultMotionState* boxMotionState = new btDefaultMotionState(
        btTransform(btQuaternion(0,0,0,1),
        btVector3(0,0,10)));
      // mass and intertia
      btScalar mass = 1;
      btVector3 boxInertia(0,0,0);
      box->calculateLocalInertia(mass,boxInertia);
      // build rigid body
      btRigidBody::btRigidBodyConstructionInfo boxRigidBodyNfo(mass,boxMotionState,box,boxInertia);
      btRigidBody* boxRigidBody = new btRigidBody(boxRigidBodyNfo);
      // add to world
      g_Physics.dynamicsWorld->addRigidBody(boxRigidBody);
      // store in list of rigid bodies for rendering
      g_Boxes.push_back( boxRigidBody );
  }
}

// ------------------------------------------------------------------

// 'mainKeyUnpressed' is called everytime a key is released
void mainKeyUnpressed(uchar key)
{

}

// ------------------------------------------------------------------

void drawMesh(TriangleMesh *m)
{
  glBegin(GL_TRIANGLES);
  ForIndex(t,m->numTriangles()) {
    ForIndex(i,3) {
      VertexData *vdta = (VertexData*)m->vertexDataAt(m->triangleAt(t)[i]);
      glNormal3fv( &vdta->nrm[0] );
      glVertex3fv( &vdta->pos[0] );
    }
  }
  glEnd();
}

// ------------------------------------------------------------------

// 'mainRender' is called everytime the screen is drawn
void mainRender()
{

  clearScreen();

  g_Sh->begin();
  
  // u_Perspective is both perspective and lookat (camera)
  g_Sh->u_Perspective.set( 
      perspectiveMatrixGL( (float)M_PI/6.0f, 1.0f, 0.01f, 100000.0f )
    * lookatMatrix( V3F(30,30,30), V3F(0,0,0), V3F(0,0,1) ) );

  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);

  // step the physics engine, use variable time step
  time_t now     = milliseconds();
  time_t el      = now - g_Physics.last;
  if (el > 1) {
    g_Physics.last = now;
    g_Physics.dynamicsWorld->stepSimulation(el/1000.0f);
  }

  ForIndex(b,g_Boxes.size()) {  
    // get transform
    btTransform trans;
    g_Boxes[b]->getMotionState()->getWorldTransform(trans);
    // compute matrix for object
    btVector3    tr = trans.getOrigin();
    btQuaternion q  = trans.getRotation();
    m4x4f        m  = translationMatrix( V3F(tr.getX(),tr.getY(),tr.getZ()) )
                    * quatf( q.getX(),q.getY(),q.getZ(),q.getW() ).toMatrix()
                    * translationMatrix( V3F(-0.5f,-0.5f,-0.5f) );
    // setup transform
    g_Sh->u_ModelView.set( m );
    // draw box
    g_Box->render();
  }

  // restore identity
  m4x4f mid; mid.eqIdentity();
  g_Sh->u_ModelView.set( mid );

  // draw scene
  drawMesh( g_Scene );

  g_Sh->end();
}

// ------------------------------------------------------------------

// 'main' is the starting point of the application
int main(int argc,const char **argv)
{
  try { // error handling

    // opens a window
    TrackballUI::init(c_ScreenW,c_ScreenH,"Bullet first test");
    // set the render function to be 'mainRender' defined above
    TrackballUI::onRender       = mainRender;
    // set the keyboard function
    TrackballUI::onKeyPressed   = mainKeyPressed;
    TrackballUI::onKeyUnpressed = mainKeyUnpressed;

    // init physics
    // -> broadphase
    g_Physics.broadphase             = new btDbvtBroadphase();
     // -> collision configuration and dispatcher
    g_Physics.collisionConfiguration = new btDefaultCollisionConfiguration();
    g_Physics.dispatcher             = new btCollisionDispatcher(g_Physics.collisionConfiguration);
    // -> physics solver
    g_Physics.solver                 = new btSequentialImpulseConstraintSolver;
    // -> The world.
    g_Physics.dynamicsWorld          = new btDiscreteDynamicsWorld(g_Physics.dispatcher,g_Physics.broadphase,g_Physics.solver,g_Physics.collisionConfiguration);
    // -> setup gravity
    g_Physics.dynamicsWorld->setGravity(btVector3(0,0,-10));
    // -> init time steps
    g_Physics.last = milliseconds();
    // -> load scene geometry
    g_Scene = loadTriangleMesh( SRC_PATH "data/scene.dae" );
    // -> add scene to bullet
     {
       // -> create a bullet indexed mesh
       // NOTE: there is some ugly pointer mechanics going on here ...
       btTriangleIndexVertexArray  *btmesh  = new btTriangleIndexVertexArray(
         g_Scene->numTriangles(), (int*)&g_Scene->triangleAt(0), 3*sizeof(int), 
         g_Scene->numVertices(), (btScalar*)g_Scene->vertexDataAt(0), sizeof(VertexData) );
       btCollisionShape      *sceneShape       = new btBvhTriangleMeshShape( btmesh, false );
       btDefaultMotionState  *sceneMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
       btRigidBody::btRigidBodyConstructionInfo sceneRigidBodyNfo(0,sceneMotionState,sceneShape,btVector3(0,0,0));
       btRigidBody           *sceneRigidBody   = new btRigidBody(sceneRigidBodyNfo);
       g_Physics.dynamicsWorld->addRigidBody(sceneRigidBody);
    }

    // -> create box geometry
    g_Box   = makeBox();

    g_Sh = new AutoBindShader::shd();
    g_Sh->init();

    // enter the main loop
    TrackballUI::loop();

    // close
    g_Sh->terminate();
    TrackballUI::shutdown();

  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }

  return 0;
}

// ------------------------------------------------------------------
