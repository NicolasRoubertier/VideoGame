// Sylvain.Lefebvre@inria.fr  2012-04-10
// ------------------------------------------------------------------

#include "../common/common.h"

#include "shd.h"
AutoBindShader::shd *g_Sh;

using namespace std;

LIBSL_WIN32_FIX;

// ------------------------------------------------------------------

#include "drawimage.h"

#include "mesh.h"
#include "grid.h"
#include "tower.h"
#include "enemy.h"

// ------------------------------------------------------------------

// Constants
const int   c_ScreenW        = 1600;
const int   c_ScreenH        = 1000;

const float c_InchesToMeter  = 1.0f / 39.3701f;

// Globals
bool         g_Keys[256];
t_mesh      *g_Border   = NULL;

// ------------------------------------------------------------------

// 'mainKeyPressed' is called everytime a key is pressed
void mainKeyPressed(uchar key)
{
  g_Keys[key] = true;
}

// ------------------------------------------------------------------

// 'mainKeyUnpressed' is called everytime a key is released
void mainKeyUnpressed(uchar key)
{
  g_Keys[key] = false;
}

// ------------------------------------------------------------------

void gameLogic()
{
  static time_t last = milliseconds();
  time_t now         = milliseconds();
  time_t elapsed     = now - last;
  last = now;
  // user inputs
  // TODO
  // animate ennemies
  // TODO
  // animate towers
  // TODO
}

// ------------------------------------------------------------------

// 'mainRender' is called everytime the screen is drawn
void mainRender()
{
  // call game logic
  gameLogic();

  // clear frame
  clearScreen();

  // draw grid
  // TODO

  // draw enemies
  // TODO

  // draw user interface
  // TODO
}

// ------------------------------------------------------------------

// 'main' is the starting point of the application
int main(int argc,const char **argv)
{
  try { // error handling

    // opens a window
    SimpleUI::init(c_ScreenW,c_ScreenH,"Defend!");
    // set the render function to be 'mainRender' defined above
    SimpleUI::onRender       = mainRender;
    // set the keyboard function
    SimpleUI::onKeyPressed   = mainKeyPressed;
    SimpleUI::onKeyUnpressed = mainKeyUnpressed;

    drawimage_init(c_ScreenW,c_ScreenH);

    // enter the main loop
    SimpleUI::loop();

    // close
    drawimage_terminate();
    SimpleUI::shutdown();

  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }

  return 0;
}

// ------------------------------------------------------------------
