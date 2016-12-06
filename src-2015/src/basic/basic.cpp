// SL 2012-02-22

// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"

LIBSL_WIN32_FIX;

// ------------------------------------------------------------------

// Constants
const int   c_ScreenW      = 800;
const int   c_ScreenH      = 600;

// Globals
DrawImage  *g_Image;

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

// 'mainRender' is called everytime the screen is drawn
void mainRender()
{
  glClear( GL_COLOR_BUFFER_BIT );
  g_Image->draw( (c_ScreenW-g_Image->w())/2 , (c_ScreenH-g_Image->h())/2 );
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

    g_Image = new DrawImage(sourcePath() + "\\data\\test.jpg");

    // enter the main loop
    SimpleUI::loop();

    // terminate
    // -> drawimage
    drawimage_terminate();
    // -> close the window
    SimpleUI::shutdown();

  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }

  return 0;
}

// ------------------------------------------------------------------
