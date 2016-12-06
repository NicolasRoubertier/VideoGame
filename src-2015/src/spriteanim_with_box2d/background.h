// Sylvain.Lefebvre@inria.fr  2015-03-10
#pragma once

// ------------------------------------------------------------------

#include<string>

using namespace std;

// ------------------------------------------------------------------

#include "drawimage.h"

// ------------------------------------------------------------------

typedef struct
{
	DrawImage* image;
	time_t tm_last_used;
}ScreenInfo;

typedef struct
{
	map<v2i, ScreenInfo>    screens;
	map<v2i, DrawImage*>    screens2;

	v2i                     viewpos;
	v2i                     pos;

	int                     screenw;
	int                     screenh;
} Background;

// ------------------------------------------------------------------

Background *background_init(int w, int h);
void        background_draw(Background*);
void loadBackground2(Background *bkg, int x, int y);
Background * background_init2(int screenw, int screenh, int x, int y);
void background_draw2(Background *bkg, v2i pos, v2i leftCorner);

// ------------------------------------------------------------------
