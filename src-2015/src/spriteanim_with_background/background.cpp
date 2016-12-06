// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"
#include "script.h"
#include "background.h"

const time_t c_ScreenDeletionDelay=10000;
// ------------------------------------------------------------------

Background *background_init(int screenw,int screenh)
{
  Background *bkg = new Background;
  bkg->screenw = screenw;
  bkg->screenh = screenh;
  return bkg;
}

// ------------------------------------------------------------------

void        background_draw(Background *bkg, v2i viewpos)
{
  // find the screen image locations required to draw
  v2i mincorner = v2i( 
    floor( 
      v2f(viewpos - v2i(bkg->screenw / 2, 0)) 
    / v2f(bkg->screenw, bkg->screenh) ) );
  v2i maxcorner = v2i(
    ceil(
      v2f(viewpos + v2i(bkg->screenw / 2, bkg->screenh ))
    / v2f(bkg->screenw, bkg->screenh)) );
  set<v2i> required;
  for (int j = mincorner[1]; j < maxcorner[1]; j++) {
    for (int i = mincorner[0]; i < maxcorner[0]; i++) {
      required.insert(v2i(i, j));
    }
  }

  // free screen images that are no longer required
  //map<v2i, DrawImage*>::iterator
  auto S = bkg->screens.begin();
  while ( S != bkg->screens.end() ) {
    // is this screen image required?
    if (required.find(S->first) == required.end()) {
		// no! delete?
		time_t now = milliseconds();
		if (now - S->second.tm_last_used > c_ScreenDeletionDelay){
			// yes : delay has expired
			cerr << "unloading screen " << S->first << endl;
			delete (S->second.image);
			S = bkg->screens.erase(S);
		} else {
			// not time of reuse
			S-> second.tm_last_used = milliseconds();
			// no: next
			S++;
		}
    } else {
      // yes, next
      S++;
    }
  }
  // load if necessary
  for (set<v2i>::iterator R = required.begin(); R != required.end(); R++) {
    // already known?
    if (bkg->screens.find(*R) == bkg->screens.end()) {
      // no: load
      string name = sourcePath() + "/src/spriteanim_with_background/screens/" + to_string((*R)[0]) + "_" + to_string((*R)[1]) + ".jpg";
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
      //map<v2i, DrawImage*>::iterator
	  auto S = bkg->screens.find(v2i(i, j));
      if (S != bkg->screens.end()) {
        // yes, draw
        S->second.image->draw(i*bkg->screenw - viewpos[0] + bkg->screenw / 2, j*bkg->screenh - viewpos[1]);
      }
    }
  }
}

// ------------------------------------------------------------------
