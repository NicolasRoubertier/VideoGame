// Sylvain.Lefebvre@inria.fr  2012-03-20
// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"
#include "sprite.h"

LIBSL_WIN32_FIX;

// ------------------------------------------------------------------

// Constants
const int    c_ScreenW      = 800;
const int    c_ScreenH      = 600;

SpriteAnim  *g_RunLeft;

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

int     g_Frame     = 0;
time_t  g_LastFrame = milliseconds();

// 'mainRender' is called everytime the screen is drawn
void mainRender()
{
  clearScreen();
    
  g_RunLeft->drawFrame( 16,16, g_Frame );

  time_t now = milliseconds();
  time_t el  = now - g_LastFrame;
  if ( el > 50 ) {
    g_LastFrame = now;
    g_Frame ++;
  }

}

// ------------------------------------------------------------------

// 'main' is the starting point of the application
int main(int argc,const char **argv)
{
  try { // error handling

    // opens a window
    SimpleUI::init(c_ScreenW,c_ScreenH,"Sprite101");
    // set the render function to be 'mainRender' defined above
    SimpleUI::onRender       = mainRender;
    // set the keyboard function
    SimpleUI::onKeyPressed   = mainKeyPressed;
    SimpleUI::onKeyUnpressed = mainKeyUnpressed;

    // init drawimage library
    drawimage_init( c_ScreenW,c_ScreenH );

    // draw sprite
    g_RunLeft = new SpriteAnim(DATA_PATH "gripe.run_left.png",32);

    // enter the main loop
    SimpleUI::loop();

    drawimage_terminate();

    // close the window
    SimpleUI::shutdown();

  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }

  return 0;
}

// ------------------------------------------------------------------
