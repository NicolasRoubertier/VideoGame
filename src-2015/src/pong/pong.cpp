// SL 2012-02-22

// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"
#include <string>   // pour std::string 

LIBSL_WIN32_FIX;

// ------------------------------------------------------------------

// Constants
const int   c_ScreenW      = 800;
const int   c_ScreenH      = 600;
int nb_collision = 0;

time_t g_LastUpdate = 0;

DrawImage *g_Ball = NULL;
v2f g_BallPos = v2f(c_ScreenW / 2, c_ScreenH / 2);
v2f g_BallSpeed = v2f(500, 100);

bool g_KeyStates[256];

class PadData {
public:
	PadData() {
		m_Pos = v2f(0, 0);
		m_Speed = 0;
		m_KeyUp = 'a';
		m_KeyDown = 'q';
		m_Score = 0;
	}
	v2f m_Pos;
	float m_Speed;
	uchar m_KeyUp;
	uchar m_KeyDown;
	int m_Score;
};

DrawImage *g_ScoreLeft = NULL;
DrawImage *g_ScoreRight = NULL;
DrawImage *g_Winner = NULL;
DrawImage *g_PadImage = NULL;
PadData *g_LeftPad = NULL;
PadData *g_RightPad = NULL;

// ------------------------------------------------------------------

// 'mainKeyPressed' is called everytime a key is pressed
void mainKeyPressed(uchar key)
{
	g_KeyStates[key] = true;
}

// ------------------------------------------------------------------

// 'mainKeyUnpressed' is called everytime a key is released
void mainKeyUnpressed(uchar key)
{
	g_KeyStates[key] = false;
}

// ------------------------------------------------------------------

// 'mainRender' is called everytime the screen is drawn
void mainRender()
{
	clearScreen(LIBSL_COLOR_BUFFER, 0.5f, 0.5f, 0.5f, 0);

	//physics
	time_t now = milliseconds();
	time_t elapsed = now - g_LastUpdate;
	if (elapsed > 10){
		// only update physics if enough time has passed

		if (g_BallSpeed[0] < 0){
			g_BallSpeed[0] = - 500 - 20 * nb_collision;
		}
		if (g_BallSpeed[1] < 0){
			g_BallSpeed[1] = -100 - 10 * nb_collision;
		}
		if (g_BallSpeed[0] > 0){
			g_BallSpeed[0] = 500 + 20 * nb_collision;
		}
		if (g_BallSpeed[1] > 0){
			g_BallSpeed[1] = 100 + 10 * nb_collision;
		}

		g_BallPos = g_BallPos + g_BallSpeed * (float)elapsed / 1000.0F;
		
		//****************************************
		// move pads and avoid pads exit on the top or on the bottom
		if ((g_KeyStates[g_LeftPad->m_KeyUp]) && (g_LeftPad->m_Pos[1] <= c_ScreenH - g_PadImage->h() / 2)) {
			g_LeftPad->m_Pos[1] = g_LeftPad->m_Pos[1] + g_LeftPad->m_Speed * (float)elapsed / 1000.0f;
		}
		if ((g_KeyStates[g_LeftPad->m_KeyDown]) && (g_LeftPad->m_Pos[1] >= g_PadImage->h() / 2)) {
			g_LeftPad->m_Pos[1] = g_LeftPad->m_Pos[1] - g_LeftPad->m_Speed * (float)elapsed / 1000.0f;
		}

		if ((g_KeyStates[g_RightPad->m_KeyUp]) && (g_RightPad->m_Pos[1] <= c_ScreenH - g_PadImage->h() / 2)) {
			g_RightPad->m_Pos[1] = g_RightPad->m_Pos[1] + g_RightPad->m_Speed * (float)elapsed / 1000.0f;
		}
		if ((g_KeyStates[g_RightPad->m_KeyDown]) && (g_RightPad->m_Pos[1] >= g_PadImage->h() / 2)) {
			g_RightPad->m_Pos[1] = g_RightPad->m_Pos[1] - g_RightPad->m_Speed * (float)elapsed / 1000.0f;
		}


		//****************************************
		// test for collisions ball with walls
		if ((g_BallPos[0] > c_ScreenW - g_Ball->w() / 2)) {
			// ball exits on the right
			g_BallSpeed[0] = -g_BallSpeed[0];
			// resolve collision
			g_BallPos[0] = c_ScreenW - g_Ball->w() / 2;
			g_LeftPad->m_Score += 1;
			nb_collision = 0;

		}
		if (g_BallPos[0] < g_Ball->w() / 2) {
			// ball exits on the left
			g_BallSpeed[0] = -g_BallSpeed[0];
			// resolve collision
			g_BallPos[0] = g_Ball->w() / 2;
			g_RightPad->m_Score += 1;
			nb_collision = 0;
		}
		if (g_BallPos[1] > c_ScreenH - g_Ball->h() / 2) {
			// ball exits on the top
			g_BallSpeed[1] = -g_BallSpeed[1];
			// resolve collision
			g_BallPos[1] = c_ScreenH - g_Ball->h() / 2;
		}
		if (g_BallPos[1] < g_Ball->h() / 2) {
			// ball exits on the bottom
			g_BallSpeed[1] = -g_BallSpeed[1];
			// resolve collision
			g_BallPos[1] = g_Ball->h() / 2;
		}


		//****************************************
		// Collision with pads
		if ((g_BallPos[0] <= g_LeftPad->m_Pos[0] + g_PadImage->w() / 2) && (g_BallPos[0] >= g_LeftPad->m_Pos[0]) && ((g_BallPos[1] <= g_LeftPad->m_Pos[1] + g_PadImage->h() / 2) && (g_BallPos[1] >= g_LeftPad->m_Pos[1] - g_PadImage->h() / 2))){
			g_BallSpeed[0] = -g_BallSpeed[0];
			g_BallPos[0] = g_LeftPad->m_Pos[0] + g_PadImage->w() / 2+g_Ball->h() / 2;
			nb_collision += 1;
		}
		if ((g_BallPos[0] >= g_RightPad->m_Pos[0] - g_PadImage->w() / 2) && (g_BallPos[0] <= g_RightPad->m_Pos[0]) && ((g_BallPos[1] <= g_RightPad->m_Pos[1] + g_PadImage->h() / 2) && (g_BallPos[1] >= g_RightPad->m_Pos[1] - g_PadImage->h() / 2))){
			g_BallSpeed[0] = -g_BallSpeed[0];
			g_BallPos[0] = g_RightPad->m_Pos[0] - g_PadImage->w() / 2 - g_Ball->h() / 2;
			nb_collision += 1;
		}


		//****************************************
		//update Scores
		if ((g_LeftPad->m_Score <= 7) && (g_RightPad->m_Score <= 7)){
			if (g_LeftPad->m_Score == 1){
				g_ScoreLeft = new DrawImage(DATA_PATH "1.png");
			}
			if (g_RightPad->m_Score == 1){
				g_ScoreRight = new DrawImage(DATA_PATH "1.png");
			}
			if (g_LeftPad->m_Score == 2){
				g_ScoreLeft = new DrawImage(DATA_PATH "2.png");
			}
			if (g_RightPad->m_Score == 2){
				g_ScoreRight = new DrawImage(DATA_PATH "2.png");
			}
			if (g_LeftPad->m_Score == 3){
				g_ScoreLeft = new DrawImage(DATA_PATH "3.png");
			}
			if (g_RightPad->m_Score == 3){
				g_ScoreRight = new DrawImage(DATA_PATH "3.png");
			}
			if (g_LeftPad->m_Score == 4){
				g_ScoreLeft = new DrawImage(DATA_PATH "4.png");
			}
			if (g_RightPad->m_Score == 4){
				g_ScoreRight = new DrawImage(DATA_PATH "4.png");
			}
			if (g_LeftPad->m_Score == 5){
				g_ScoreLeft = new DrawImage(DATA_PATH "5.png");
			}
			if (g_RightPad->m_Score == 5){
				g_ScoreRight = new DrawImage(DATA_PATH "5.png");
			}
			if (g_LeftPad->m_Score == 6){
				g_ScoreLeft = new DrawImage(DATA_PATH "6.png");
			}
			if (g_RightPad->m_Score == 6){
				g_ScoreRight = new DrawImage(DATA_PATH "6.png");
			}
			if (g_LeftPad->m_Score >= 7){
				g_ScoreLeft = new DrawImage(DATA_PATH "7.png");
				g_Winner = new DrawImage(DATA_PATH "player1.png");
			}
			if (g_RightPad->m_Score >= 7){
				g_ScoreRight = new DrawImage(DATA_PATH "7.png");
				g_Winner = new DrawImage(DATA_PATH "player2.png");
			}
		
		}
		
		g_LastUpdate = now;
	}

	//render
	g_ScoreLeft->draw(c_ScreenW / 4 - g_ScoreLeft->w() / 2, 7.0 / 8 * c_ScreenH -0* g_ScoreLeft->h() / 2);
	g_ScoreRight->draw(c_ScreenW * 3 / 4 - g_ScoreLeft->w() / 2, 7.0 / 8 * c_ScreenH - 0 * g_ScoreLeft->h() / 2);
	if (g_Winner != NULL){
		g_Winner->draw(c_ScreenW / 2 - g_Winner->w() / 2, c_ScreenH / 2 - g_Winner->h());
	}
	g_Ball->draw(g_BallPos[0] - g_Ball->w()/2, g_BallPos[1] - g_Ball->h()/2);
	g_PadImage->draw(g_LeftPad->m_Pos[0] - g_PadImage->w() / 2, g_LeftPad->m_Pos[1] - g_PadImage->h() / 2);
	g_PadImage->draw(g_RightPad->m_Pos[0] - g_PadImage->w() / 2, g_RightPad->m_Pos[1] - g_PadImage->h() / 2);
	
}

// ------------------------------------------------------------------

// 'main' is the starting point of the application
int main(int argc,const char **argv)
{
  try { // error handling

    // opens a window
    SimpleUI::init(c_ScreenW,c_ScreenH,"Pong");
    // set the render function to be 'mainRender' defined above
    SimpleUI::onRender       = mainRender;
    // set the keyboard function
    SimpleUI::onKeyPressed   = mainKeyPressed;
    SimpleUI::onKeyUnpressed = mainKeyUnpressed;

    // Init 
	drawimage_init(c_ScreenW, c_ScreenH);
	g_Ball = new DrawImage(DATA_PATH "ball.png");
	g_PadImage = new DrawImage(DATA_PATH "pad.png");
	g_ScoreLeft = new DrawImage(DATA_PATH "0.png");
	g_ScoreRight = new DrawImage(DATA_PATH "0.png");


	g_LeftPad = new PadData();
	g_LeftPad->m_Pos = v2f(50, c_ScreenH / 2);
	g_LeftPad->m_Speed = 300.0f;
	g_LeftPad->m_KeyUp = 'a';
	g_LeftPad->m_KeyDown = 'q';

	g_RightPad = new PadData();
	g_RightPad->m_Pos = v2f(c_ScreenW - 50, c_ScreenH / 2);
	g_RightPad->m_Speed = 300.0f;
	g_RightPad->m_KeyUp = 'p';
	g_RightPad->m_KeyDown = 'm';

	for (int i = 0; i < 256; i++) {
		g_KeyStates[i] = false;
	}
    
	g_LastUpdate = milliseconds();

    // enter the main loop
    SimpleUI::loop();

    // close the window
	drawimage_terminate;
    SimpleUI::shutdown();

  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }

  return 0;
}

// ------------------------------------------------------------------
