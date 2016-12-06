// Sylvain.Lefebvre@inria.fr  2012-04-10
// ------------------------------------------------------------------

#include "../common/common.h"

#include "shd.h"

LIBSL_WIN32_FIX;

// ------------------------------------------------------------------

// Constants
const int   c_ScreenW     = 1024;
const int   c_ScreenH     = 768;

Tex2DRGBA  *g_Color       = NULL;
Tex2DRGBA  *g_Specular    = NULL;
Tex2DRGBA  *g_Normal      = NULL;

AutoBindShader::shd *g_Sh = NULL;

IndexedVertexBuffer *g_Quad      = NULL;

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

  g_Sh->u_Projection.set( perspectiveMatrixGL(
     (float)M_PI/6.0f, 
     (float)c_ScreenW/c_ScreenH, 
     0.1f, 100.0f ) );
  m4x4f mview = translationMatrix(V3F(0,0,-4)) * TrackballUI::matrix();
  g_Sh->u_View       .set( mview );
  g_Sh->u_ViewInverse.set( mview.inverse() );
  m4x4f mid;
  mid.eqIdentity();
  g_Sh->u_Model.set( mid );

  glActiveTextureARB( GL_TEXTURE2 );
  glBindTexture     ( GL_TEXTURE_2D, g_Specular->handle() );
  g_Sh->u_Specular.set ( 2 );

  glActiveTextureARB( GL_TEXTURE1 );
  glBindTexture     ( GL_TEXTURE_2D, g_Normal->handle() );
  g_Sh->u_Normal.set ( 1 );

  glActiveTextureARB( GL_TEXTURE0 );
  glBindTexture     ( GL_TEXTURE_2D, g_Color->handle() );
  g_Sh->u_Color.set ( 0 );

  g_Quad->render();

  g_Sh->end();

}

// ------------------------------------------------------------------

// 'main' is the starting point of the application
int main(int argc,const char **argv)
{
  try { // error handling

    // opens a window
    TrackballUI::init(c_ScreenW,c_ScreenH,"Lighting");
    // set the render function to be 'mainRender' defined above
    TrackballUI::onRender       = mainRender;
    // set the keyboard function
    TrackballUI::onKeyPressed   = mainKeyPressed;
    TrackballUI::onKeyUnpressed = mainKeyUnpressed;

    g_Sh = new AutoBindShader::shd();
    g_Sh->init();

    g_Quad = new IndexedVertexBuffer();
    g_Quad->begin( GPUMESH_TRIANGLELIST );

    g_Quad->texcoord0_2( 0,  0);
    g_Quad->vertex_3   ( -1,-1,0 ); // 0
    
    g_Quad->texcoord0_2(  1, 0);
    g_Quad->vertex_3   (  1,-1,0 ); // 1
    
    g_Quad->texcoord0_2(  1, 1);
    g_Quad->vertex_3   (  1, 1,0 ); // 2
    
    g_Quad->texcoord0_2(  0, 1);
    g_Quad->vertex_3   ( -1, 1,0 ); // 3

    g_Quad->index( 0 );
    g_Quad->index( 1 );
    g_Quad->index( 2 );

    g_Quad->index( 0 );
    g_Quad->index( 2 );
    g_Quad->index( 3 );

    g_Quad->end();

    // load a texture
    ImageRGBA *image;
    
    image      = loadImageRGBA( DATA_PATH "concrete_011_Diffuse.png" );
    g_Color    = new Tex2DRGBA( image->pixels() );
    
    image      = loadImageRGBA( DATA_PATH "concrete_011_Normal.png" );
    g_Normal   = new Tex2DRGBA( image->pixels() );
    
    image      = loadImageRGBA( DATA_PATH "concrete_011_Specular.png" );
    g_Specular = new Tex2DRGBA( image->pixels() );

    // enter the main loop
    TrackballUI::loop();

    // close the window
    TrackballUI::shutdown();

  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }

  return 0;
}

// ------------------------------------------------------------------
