// SL 2012-02-22

// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"

using namespace std;

// ------------------------------------------------------------------

// Constants
const int   c_ScreenW      = 800;
const int   c_ScreenH      = 800;

TriangleMesh  *g_Mesh = NULL;
v3f            g_Eye;

map<string,Tex2DRGBA*> g_Textures;

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

// draw mesh without textures
void drawMesh(TriangleMesh *mesh)
{
  glBegin(GL_TRIANGLES);
  ForIndex(t,mesh->numTriangles()) {
    v3u tri = mesh->triangleAt(t);
    ForIndex(v,3) {
      VertexData *vertex = (VertexData*)mesh->vertexDataAt(tri[v]);
      glNormal3fv( &vertex->nrm[0] );
      glVertex3fv( &vertex->pos[0] );
    }
  }
  glEnd();
}

// ------------------------------------------------------------------

// draw mesh with textures
void drawTexturedMesh(TriangleMesh *mesh)
{
  // for each surface
  ForIndex(s,mesh->numSurfaces()) {
    // bind the texture to the texture unit
    glBindTexture(GL_TEXTURE_2D, g_Textures[mesh->surfaceTextureName(s)]->handle() );
    // draw triangles for the surface
    glBegin(GL_TRIANGLES);
    ForIndex(i,mesh->surfaceNumTriangles(s)) {
      int t   = mesh->surfaceTriangleIdAt(s,i);
      v3u tri = mesh->triangleAt(t);
      ForIndex(v,3) {
        VertexData *vertex = (VertexData*)mesh->vertexDataAt(tri[v]);
        glTexCoord2fv( &vertex->uv[0]  );
        glNormal3fv  ( &vertex->nrm[0] );
        glVertex3fv  ( &vertex->pos[0] );
      }
    }
    glEnd();
  }
}

// ------------------------------------------------------------------

// 'mainRender' is called everytime the screen is drawn
void mainRender()
{
  // clear the view (color and depth)
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  // this variable is an angle changing with time
  float agl = milliseconds()/1000.0f;

  // start using the shader
  g_Shader.begin();
  // set up matrices
  g_Shader.Proj .set( perspectiveMatrixGL((float)M_PI/4.0f, 1.0f, 0.1f, 10000.0f) );
  g_Shader.View .set( lookatMatrix( 
    g_Eye,
    v3f(0), 
    V3F(0,0,1) ) 
    );
  // set eye position
  g_Shader.u_Eye.set( g_Eye );
  // set light position
  g_Shader.u_Light0Pos.set( V3F(100*cos(agl/2),100*sin(agl/4),50) );
  // set model matrix
  g_Shader.Model.set( rotationMatrix( agl, V3F(0,0,1) ) );
  // set image texture unit
  g_Shader.u_Image.set( 0 );
  // activate texture unit 0 (the u_Image.set(*0*) above is because we use GL_TEXTURE*0* below)
  glActiveTextureARB( GL_TEXTURE0 );
  // draw mesh using textures
  drawTexturedMesh( g_Mesh );
  // stop using the shader
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
    
    // load the mesh
    g_Mesh = loadTriangleMesh( (sourcePath() + "/data/textured.dae").c_str() );
    g_Mesh->centerOn( v3f(0) );

    // select eye position
    g_Eye  = v3f(100.0f,100.0f,100.0f);

    // load all texture images
    ImageRGBA empty(64,64);
    g_Textures["default"] = new Tex2DRGBA(empty.pixels());
    // for all surfaces
    ForIndex(s,g_Mesh->numSurfaces()) {
      // get texture name
      std::cerr << g_Mesh->surfaceTextureName(s);
      // check whether we already loaded it
      if (g_Textures.find( g_Mesh->surfaceTextureName(s) ) == g_Textures.end() ) {
        // no: load!
        std::cerr << " [loading] ";
        // load image (CPU)
        string filename = sourcePath() + "/data/" + g_Mesh->surfaceTextureName(s);
        ImageRGBA *img = loadImageRGBA( filename );
        // create texture (GPU)
        g_Textures[ g_Mesh->surfaceTextureName(s) ] = new Tex2DRGBA( img->pixels() );
        // we no longer need the CPU version of the image, delete
        delete (img);
      }
      std::cerr << std::endl;
    }

    // -> init our shader
    g_Shader.init();

    // enter the main loop
    SimpleUI::loop();

    // terminate
    // -> drawimage
    drawimage_terminate();
    // -> shader
    g_Shader.terminate();
    // -> close the window
    SimpleUI::shutdown();

  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }

  return 0;
}

// ------------------------------------------------------------------
