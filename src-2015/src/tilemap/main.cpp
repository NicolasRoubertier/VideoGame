// Sylvain.Lefebvre@inria.fr  2015-03-10
// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"

LIBSL_WIN32_FIX;

// ------------------------------------------------------------------

#include "tilemap.h"

// ------------------------------------------------------------------

// Constants
const int    c_ScreenW = 800;
const int    c_ScreenH = 600;

time_t       g_LastFrame = 0;   // time when the last image has been drown

bool         g_Keys[256];    // array of keys

Tilemap     *g_Tilemap = NULL;

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

// 'mainRender' is called everytime the screen is drawn
void mainRender()
{
	// compute elapsed time
	time_t now = milliseconds();
	time_t el = now - g_LastFrame;
	if (el > 50) {
		g_LastFrame = now;
	}

	clearScreen();

	tilemap_draw(g_Tilemap);

	// reload tilemap?
	if (g_Keys[' ']) {
		g_Tilemap = tilemap_load("test.lua");
		g_Keys[' '] = false;
	}
}

// ------------------------------------------------------------------

// 'main' is the starting point of the application
int main(int argc, const char **argv)
{
	try { // error handling

		// C++ tests

		string str = "blablabla";
		str += "1234";

		cerr << str << endl; // ~ printf

		const char *tmp = str.c_str();
		printf("string is %s\n", tmp);

		map<string, int> dict;
		dict["flower"] = 3;
		dict["house"] = 17;
		cerr << "value for house : " << dict["house"] << endl;
		cerr << "value for steak : " << dict["steak"] << endl;

		if (dict.find("steak") == dict.end()){   // dict.end() = index of the last element + 1
			cerr << "steak is not here!" << endl;
		}
		else{
			cerr << "value for steak : " << dict["steak"] << endl;
		}

		for (auto M = dict.begin(); M != dict.end(); M++){   // for (first chosen index; until M != dict.end(); implements M)   auto = forces C++ to find the right type
			cerr << M->first << endl;   // key
			cerr << M->second << endl;  // value
			cerr << "-----------" << endl;
		}

		// opens a window
		SimpleUI::init(c_ScreenW, c_ScreenH, "Tilemap");
		// set the render function to be 'mainRender' defined above
		SimpleUI::onRender = mainRender;
		// set the keyboard function
		SimpleUI::onKeyPressed = mainKeyPressed;
		SimpleUI::onKeyUnpressed = mainKeyUnpressed;

		// init drawimage library
		drawimage_init(c_ScreenW, c_ScreenH);
		// keys
		for (int i = 0; i < 256; i++) {
			g_Keys[i] = false;
		}

		// load a tilemap
		g_Tilemap = tilemap_load("test.lua");

		// enter the main loop
		SimpleUI::loop();

		drawimage_terminate();

		// close the window
		SimpleUI::shutdown();

	}
	catch (Fatal& f) { // error handling
		std::cerr << Console::red << f.message() << Console::gray << std::endl;
	}

	return 0;
}

// ------------------------------------------------------------------