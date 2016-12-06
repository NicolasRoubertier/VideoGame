// Sylvain.Lefebvre@inria.fr  2012-03-20
#pragma once

// ------------------------------------------------------------------

#include "drawimage.h"

// ------------------------------------------------------------------

class SpriteAnim
{
private:

  DrawImage *m_Table;
  int        m_NumFrames;
  int        m_FrameWidth;

public:

  SpriteAnim(const char *image,int frameWidth);
  
  void drawFrame(int x,int y, int frame, float scale=1.0f );

};

// ------------------------------------------------------------------
