
#include "common.h"
#include "drawimage.h"

LIBSL_WIN32_FIX;

using namespace std;

time_t g_StartTm = milliseconds();

DrawImage *g_Image;

// 'main' is the starting point of the application
int main(int argc,const char **argv)
{
  
  g_Image = new DrawImage( DATA_PATH "test.png" );
  cerr << g_Image->w() << 'x' << g_Image->h() << endl;

  cerr << "Hello world" << endl;

  return 0;

}


