// Sylvain.Lefebvre@inria.fr  2012-04-10
// ------------------------------------------------------------------

#include "common.h"

LIBSL_WIN32_FIX;

#include "shd.h"
AutoBindShader::shd *g_Sh = NULL;

// ------------------------------------------------------------------

// Constants
const int   c_ScreenW      = 800;
const int   c_ScreenH      = 600;

// ------------------------------------------------------------------

IndexedVertexBuffer *g_VB   = NULL;
TriangleMesh        *g_Mesh = NULL;

// ------------------------------------------------------------------

// 'mainKeyPressed' is called everytime a key is pressed
void mainKeyPressed(uchar key)
{

}

// ------------------------------------------------------------------

// 'mainKeyUnpressed' is called everytime a key is released
void mainKeyUnpressed(uchar key)
{

}

// ------------------------------------------------------------------

// 'mainRender' is called everytime the screen is drawn
void mainRender()
{

  clearScreen();

  g_Sh->begin();

  m4x4f persp = perspectiveMatrixGL( (float)M_PI/6.0f, 1.0f, 0.01f, 1000.0f );
  m4x4f lkat  = lookatMatrix( V3F(10,10,10), g_Mesh->bbox().center(), V3F(0,0,1) );

  static float r = 0.0f;
  r += M_PI / 500.0f;

  g_Sh->u_Perspective.set( persp );
  g_Sh->u_ModelView  .set( lkat * quatf(V3F(0,0,1),r).toMatrix() );

  g_VB->render();

  g_Sh->end();

}

// ------------------------------------------------------------------

// 'main' is the starting point of the application
int main(int argc,const char **argv)
{
  try { // error handling

    // opens a window
    TrackballUI::init(c_ScreenW,c_ScreenH,"Viewer 3D");
    // set the render function to be 'mainRender' defined above
    TrackballUI::onRender       = mainRender;
    // set the keyboard function
    TrackballUI::onKeyPressed   = mainKeyPressed;
    TrackballUI::onKeyUnpressed = mainKeyUnpressed;

    g_Mesh = loadTriangleMesh(SRC_PATH "torus.3ds");
    g_VB = new IndexedVertexBuffer();
    g_VB->begin( GPUMESH_TRIANGLELIST );
    for (int v = 0;v<g_Mesh->numVertices();v++) {
      
      MeshFormat_3DS::t_VertexData *d = (MeshFormat_3DS::t_VertexData*)g_Mesh->vertexDataAt(v);
      g_VB->color0_3( d->pos[0],d->pos[1],d->pos[2] );
      g_VB->vertex_3( d->pos[0],d->pos[1],d->pos[2] );

    }
    for (int t = 0 ; t < g_Mesh->numTriangles() ; t ++) {
      g_VB->index( g_Mesh->triangleAt(t)[0] );
      g_VB->index( g_Mesh->triangleAt(t)[1] );
      g_VB->index( g_Mesh->triangleAt(t)[2] );
    }
    g_VB->end();

    g_Sh = new AutoBindShader::shd();
    g_Sh->init();

    // enter the main loop
    TrackballUI::loop();

    // close the window
    g_Sh->terminate();
    TrackballUI::shutdown();

  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }

  return 0;
}

// ------------------------------------------------------------------
