// Sylvain.Lefebvre@inria.fr  2012-03-20
#include "sprite.h"

// ------------------------------------------------------------------

SpriteAnim::SpriteAnim(const char *image,int frameWidth)
{
  m_Table        = new DrawImage(image);
  m_FrameWidth   = frameWidth;
  m_NumFrames    = m_Table->w() / frameWidth;
}

// ------------------------------------------------------------------

void SpriteAnim::drawFrame(int x,int y, int frame, float scale )
{
  frame = frame % m_NumFrames;
  m_Table->drawSub( 
    V2I(x,y), V2I(m_FrameWidth*scale,m_Table->h()*scale), 
    V2I(frame*m_FrameWidth,0), V2I(m_FrameWidth,m_Table->h()) );
}

// ------------------------------------------------------------------
