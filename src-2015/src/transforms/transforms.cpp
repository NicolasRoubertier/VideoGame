// SL 2012-02-22

// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"

LIBSL_WIN32_FIX;

// ------------------------------------------------------------------

// Constants
const int   c_ScreenW      = 800;
const int   c_ScreenH      = 600;

TriangleMesh *g_Mesh = NULL;

// ------------------------------------------------------------------

#include "shader_sh.h"
AutoBindShader::shader_sh g_Shader;

// ------------------------------------------------------------------

// 'mainKeyPressed' is called everytime a key is pressed
void mainKeyPressed(uchar key)
{
  // TODO
}

// ------------------------------------------------------------------

// 'mainKeyUnpressed' is called everytime a key is released
void mainKeyUnpressed(uchar key)
{
  // TODO
}

// ------------------------------------------------------------------

void drawMesh(TriangleMesh *mesh)
{
  glBegin(GL_TRIANGLES);
  ForIndex(t,mesh->numTriangles()) {
    v3u tri = mesh->triangleAt(t);
    ForIndex(v,3) {
      VertexData *vertex = (VertexData*)mesh->vertexDataAt(tri[v]);
      glNormal3f( vertex->nrm[0],vertex->nrm[1],vertex->nrm[2] );
      v3f pt = vertex->pos * v3f(2.54) /*inches to centimeters*/;
      glVertex3f( pt[0],pt[1],pt[2] );
    }
  }
  glEnd();
}

// ------------------------------------------------------------------

// 'mainRender' is called everytime the screen is drawn
void mainRender()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  g_Shader.begin();
  // perspective matrix
  g_Shader.Proj .set( perspectiveMatrixGL((float)M_PI/4.0f, 1.0f, 0.1f, 10000.0f) );
  // view matrix
  g_Shader.View .set( lookatMatrix(
    v3f(-400,-400,500), // eye
    v3f(50,50,25),      // target
    v3f(0,0,1) )        // up
    );

  // draw the model once
  g_Shader.Model.set( m4x4f::identity() );
  drawMesh( g_Mesh );


  g_Shader.end();
}

// ------------------------------------------------------------------

// 'main' is the starting point of the application
int main(int argc,const char **argv)
{
  try { // error handling

    // opens a window
    SimpleUI::init(c_ScreenW,c_ScreenH,"Basic framework");
    // set the render function to be 'mainRender' defined above
    SimpleUI::onRender       = mainRender;
    // set the keyboard function
    SimpleUI::onKeyPressed   = mainKeyPressed;
    SimpleUI::onKeyUnpressed = mainKeyUnpressed;

    // init 
    // -> drawimage
    drawimage_init(c_ScreenW,c_ScreenH);
    g_Shader.init();

    g_Mesh = loadTriangleMesh( (sourcePath() + "/data/test.dae").c_str() );

    // enter the main loop
    SimpleUI::loop();

    // terminate
    // -> drawimage
    drawimage_terminate();
    g_Shader.terminate();
    // -> close the window
    SimpleUI::shutdown();

  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }

  return 0;
}

// ------------------------------------------------------------------
