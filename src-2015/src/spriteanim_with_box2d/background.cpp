// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"
#include "script.h"
#include "background.h"

const time_t c_ScreenDeletionDelay = 10000;
// ------------------------------------------------------------------

Background *background_init(int screenw, int screenh)
{
	Background *bkg = new Background;
	bkg->viewpos = v2i(screenw / 2, 0);
	bkg->screenw = screenw;
	bkg->screenh = screenh;
	return bkg;
}

// ------------------------------------------------------------------

void        background_draw(Background *bkg)
{
	// find the screen image locations required to draw
	v2i mincorner = v2i(
		floor(
		v2f(bkg->viewpos - v2i(bkg->screenw / 2, 0))
		/ v2f(bkg->screenw, bkg->screenh)));
	v2i maxcorner = v2i(
		ceil(
		v2f(bkg->viewpos + v2i(bkg->screenw / 2, bkg->screenh))
		/ v2f(bkg->screenw, bkg->screenh)));
	set<v2i> required;
	for (int j = mincorner[1]; j < maxcorner[1]; j++) {
		for (int i = mincorner[0]; i < maxcorner[0]; i++) {
			required.insert(v2i(i, j));
		}
	}
	// free screen images that are no longer required
	auto S = bkg->screens.begin();
	while (S != bkg->screens.end()) {
		// is this screen image required?
		if (required.find(S->first) == required.end()) {
			time_t now = milliseconds();
			if (now - S->second.tm_last_used > c_ScreenDeletionDelay)
			{
				// no! delete
				cerr << "unloading screen " << S->first << endl;
				delete (S->second.image);
				S = bkg->screens.erase(S);
			}
			else{
				// no => next
				S++;
			}
		}
		else {
			// note time of re-use
			S->second.tm_last_used = milliseconds();
			// yes, next
			S++;
		}
	}
	// load if necessary
	for (set<v2i>::iterator R = required.begin(); R != required.end(); R++) {
		// already known?
		if (bkg->screens.find(*R) == bkg->screens.end()) {
			// no: load
			string name = executablePath() + "/data/screens/" + to_string((*R)[0]) + "_" + to_string((*R)[1]) + ".jpg";
			// cerr << "attemtping to load " << name << endl;
			if (LibSL::System::File::exists(name.c_str())) {
				DrawImage *image = new DrawImage(name.c_str());
				ScreenInfo si;
				si.image = image;
				si.tm_last_used = milliseconds();
				bkg->screens[*R] = si;
			}
		}
	}
	// draw!
	for (int j = mincorner[1]; j < maxcorner[1]; j++) {
		for (int i = mincorner[0]; i < maxcorner[0]; i++) {
			// check if image is loaded
			auto S = bkg->screens.find(v2i(i, j));
			if (S != bkg->screens.end()) {
				// yes, draw
				S->second.image->draw(i*bkg->screenw - bkg->viewpos[0] + bkg->screenw / 2, j*bkg->screenh + bkg->viewpos[1]);
			}
		}
	}
}

Background *background_init2(int screenw, int screenh, int x, int y)
{
	Background *bkg = new Background;
	bkg->pos = v2i(x, y);
	bkg->screenw = screenw;
	bkg->screenh = screenh;
	loadBackground2(bkg, x, y);
	return bkg;
}

void loadBackground2(Background *bkg, int x, int y) {
	if (bkg->screens2.find(v2i(x, y)) != bkg->screens2.end()) {
		return;
	}
	bool failed = false;
	DrawImage* puzzle;
	string name = executablePath()  + "/data/screens/" + to_string(x) + "_" + to_string(y) + ".jpg";
	if (LibSL::System::File::exists(name.c_str())) {
		puzzle = new DrawImage(name.c_str(), v3b(255, 0, 255));
	}

	else {
		failed = true;
		std::cerr << Console::red << "failed" << Console::gray << std::endl;
	}
	if (!failed) {
		bkg->screens2[v2i(x, y)] = puzzle;
		std::cerr << Console::red << bkg->screens.size() << Console::gray << std::endl;
	}
}

void background_draw2(Background *bkg, v2i pos, v2i leftCorner) {
	for (int i = 0; i < 3; i++) {
		bkg->screens2[pos]->draw(leftCorner[0], leftCorner[1]);
	}
}

// ------------------------------------------------------------------
