// SL 2012-02-22

// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"

LIBSL_WIN32_FIX;

// ---------------------------------------------------

extern "C" {
#include <lua.h>
#include <lualib.h>
}

#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/operator.hpp>
#include <luabind/exception_handler.hpp>

using namespace luabind;

// ------------------------------------------------------------------

#include <cstdio>

using namespace std;

// ------------------------------------------------------------------

// Constants
const int   c_ScreenW      = 800;
const int   c_ScreenH      = 600;

// Globals
lua_State  *g_LuaState = NULL;
bool        g_Keys[256];
uint        g_Elapsed  = 0;

// ------------------------------------------------------------------

typedef struct {
  DrawImage *image;
  float  x;
  float  y;
  bool   alive;
} t_Entity;

vector<t_Entity*> g_Entities;

// ------------------------------------------------------------------

void lua_log(string s)
{
  cerr << "[lua] " << s << endl;
}

int lua_spawn(int x,int y,string img)
{
  t_Entity *e = new t_Entity;
  e->x     = x;
  e->y     = y;
  e->alive = true;
  e->image = new DrawImage(sourcePath() + "\\data\\" + img + ".png");
  g_Entities.push_back(e);
  return g_Entities.size()-1;
}

void lua_move(int e,int dx,int dy)
{
  sl_assert( e < g_Entities.size() && e >= 0 );
  g_Entities[e]->x += (float)dx * (float)g_Elapsed / 10.0f;
  g_Entities[e]->y += (float)dy * (float)g_Elapsed / 10.0f;
}

// ------------------------------------------------------------------

// 'mainKeyPressed' is called everytime a key is pressed
void mainKeyPressed(uchar key)
{
  g_Keys[ key ] = true;
}

// ------------------------------------------------------------------

// 'mainKeyUnpressed' is called everytime a key is released
void mainKeyUnpressed(uchar key)
{
  g_Keys[ key ] = false;
}

// ------------------------------------------------------------------

AAB<2> entity_box(int e)
{
  AAB<2> box;
  box.addPoint( v2f(
    g_Entities[e]->x - (int)g_Entities[e]->image->w()/2,
    g_Entities[e]->y - (int)g_Entities[e]->image->h()/2) );
  box.addPoint( v2f(
    g_Entities[e]->x + (int)g_Entities[e]->image->w()/2,
    g_Entities[e]->y + (int)g_Entities[e]->image->h()/2) );
  return box;
}

// ------------------------------------------------------------------

// 'mainRender' is called everytime the screen is drawn
void mainRender()
{
  static uint last = milliseconds();
  uint now = milliseconds();

  uint el = now - last;
  if (el > 5) {
    g_Elapsed = el;
    last = now;
  } else {
    return;
  }

  // step Lua script
  lua_State *L = g_LuaState;
  
  // -> set up variables
  //    -> keys
  for (int i = 'a' ; i <= 'z' ; i++) {
    string name = "Key__";
    name[4] = (char)i;
    globals(L)[name] = g_Keys[i];
  }

  // -> call step function
  try {
    call_function<void>(L,"step");
  } catch (luabind::error& e) {
    cerr << e.what() << ' ' << endl;
    exit(-1);
  }

  // -> check for contact
  for (int a=0 ; a < g_Entities.size() ; a++ ) {
    for (int b=a+1 ; b < g_Entities.size() ; b++ ) {
      if (g_Entities[a]->alive && g_Entities[b]->alive) {
        if (entity_box(a).intersect(entity_box(b))) {
          call_function<void>(L,"contact",a,b);
        }
      }
    }
  }

  // clear screen
  glClear( GL_COLOR_BUFFER_BIT );

  // draw entities
  for (int e=0 ; e < g_Entities.size() ; e++ ) {
    if (g_Entities[e]->alive) {
      g_Entities[e]->image->draw( 
        g_Entities[e]->x - g_Entities[e]->image->w()/2,
        g_Entities[e]->y - g_Entities[e]->image->h()/2 );
    }
  }

}

// ------------------------------------------------------------------

void lua_init()
{
  sl_assert( g_LuaState == NULL );

  // lua
  lua_State *L = lua_open();
  g_LuaState = L;

  luabind::open(L);

  lua_pushcfunction(L, luaopen_base);
  lua_pushliteral(L, "");
  lua_call(L, 1, 0);

  lua_pushcfunction(L, luaopen_math);
  lua_pushliteral(L, LUA_TABLIBNAME);
  lua_call(L, 1, 0);

  lua_pushcfunction(L, luaopen_table);
  lua_pushliteral(L, LUA_TABLIBNAME);
  lua_call(L, 1, 0);

  lua_pushcfunction(L, luaopen_package);
  lua_pushliteral(L, LUA_TABLIBNAME);
  lua_call(L, 1, 0);

  lua_pushcfunction(L, luaopen_string);
  lua_pushliteral(L, LUA_TABLIBNAME);
  lua_call(L, 1, 0);

  {
    module(L)
      [
        def("log",   &lua_log),
        def("spawn", &lua_spawn),
        def("move",  &lua_move)
      ];
  }

  int ret = 0;
  try {
    string path    = sourcePath() + "/script.lua";
    string program = loadFileIntoString( path.c_str() );
    ret            = luaL_dostring(L, program.c_str());
  } catch (Fatal& f) {
    cerr << Console::yellow;
    cerr << f.message() << endl;
    cerr << Console::gray;
  }
  if (ret) {
    char str[4096];
    sprintf(str,"[[LUA]exit] %s", lua_tostring(L, -1));
    cerr << Console::yellow;
    cerr << str;
    cerr << Console::gray;
  }

}

// ------------------------------------------------------------------

void lua_terminate()
{
  sl_assert( g_LuaState != NULL );
  lua_close(g_LuaState);
  g_LuaState = NULL;
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
    // -> Lua
    lua_init();

    for (int i = 0; i < 256 ; i++ ) {
      g_Keys[i] = false;
    }

    // enter the main loop
    SimpleUI::loop();

    // terminate
    // -> drawimage
    drawimage_terminate();
    // -> Lua
    lua_terminate();
    // -> close the window
    SimpleUI::shutdown();

  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }

  return 0;
}

// ------------------------------------------------------------------
