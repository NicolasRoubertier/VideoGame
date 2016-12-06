// Sylvain.Lefebvre@inria.fr  2015-03-10
#pragma once

// ------------------------------------------------------------------

#include<string>

using namespace std;

// ------------------------------------------------------------------

#include "drawimage.h"

// ------------------------------------------------------------------


typedef struct {
	DrawImage *image;
	time_t tm_last_used;
} ScreenInfo;

typedef struct
{
  map<v2i, ScreenInfo>    screens;  
  int                     screenw;
  int                     screenh;
} Background;

// ------------------------------------------------------------------

Background *background_init(int w, int h);
void        background_draw(Background*,v2i viewpos);

// ------------------------------------------------------------------
