// Sylvain.Lefebvre@inria.fr  2015-03-10

//x pour commencer
//o pour simuler la fin
//r pour redemarrer
// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"

LIBSL_WIN32_FIX;

// ------------------------------------------------------------------

#include "tilemap.h"
#include "entity.h"
#include "background.h"
#include "physics.h"
#include "sound.h"
#include "time.h"


// ------------------------------------------------------------------

// Constants

int    c_ScreenW = 650;
int    c_ScreenH = 800;
int    separation = 150;
int    ratio_split = 2;

// ------------------------------------------------------------------

time_t          g_LastFrame = 0;
time_t          g_Music =0;
bool            g_Keys[256];
int i = 0;
int r = 0;
Tilemap        *g_Tilemap = NULL;
Background     *g_Bkg1 = NULL;
Background     *g_Bkg2 = NULL;
Background     *g_HomeBkg = NULL;
Background     *g_PauseBkg = NULL;
Background     *g_EndBkg = NULL;


DrawImage      *g_Separation = NULL;
DrawImage      *i_1Heart = NULL;
DrawImage      *i_2Heart = NULL; 
DrawImage      *i_3Heart = NULL;
DrawImage      *i_4Heart = NULL;
DrawImage      *i_0Score = NULL;
DrawImage      *i_1Score = NULL;
DrawImage      *i_2Score = NULL;
DrawImage      *i_3Score = NULL;






enum state { waiting_to_start, playing, waiting_to_restart , end_of_the_game} g_State;

vector<Entity*> g_Entities;
vector<v2f>     g_Stars2;
vector<v3i>     g_Ennemies;
vector<v3i>     g_Stars;
vector<v3i>     g_Gems;
vector<v2f>     g_Gems2;
Entity*         g_Player1 = NULL;
Entity*         g_Player2 = NULL;

v2i 			g_viewpos1 = NULL;
v2i 			g_viewpos2 = NULL;

int             numFootContacts1 = 0;
int             numLeftContacts1 = 0;
int             numRightContacts1 = 0;
int             numFootContacts2 = 0;
int             numLeftContacts2 = 0;
int             numRightContacts2 = 0;
int             star;
int             five[12] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int             twelve[8] = { -1, -1, -1, -1, -1, -1, -1, -1};
int             whereIsTheStar;
int             whereIsDiamond0;
int             whereIsDiamond1;
int             whereIsBall0;
int             whereIsBall1;
bool            isInArray;
int             field;
int             lastField;
int		        doubleJump1 = 0;
int             doubleJump2 = 0;
string			monster;
string			barrel_r;
string			barrel_l;
string			spikes;
string			level;
string			ball;
string          music[6] = {"629681_-FlyBoyampGabberGir.wav", "629975_Power-Play.wav", "630254_Corriamo.wav", "630325_100-Miles.wav", "630320_Roys-Our-Boy-Smash-.wav", "630701_Mega-Man-Battle-Net.wav"};
string          theme;

// ------------------------------------------------------------------

// 'mainKeyPressed' is called everytime a key is pressed
void mainKeyPressed(uchar key)
{
	g_Keys[key] = true;


	/*if (key == 'v' && (numFootContacts1 > 0 || numLeftContacts1 > 0 || numRightContacts1 > 0)) {
		play_sound("saut.wav");
	}


	if (key == 'n' && (numFootContacts2 > 0 || numLeftContacts2 > 0 || numRightContacts2 > 0)) {
		play_sound("saut.wav");
	}*/

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
	//// Compute elapsed time
	time_t now = milliseconds();
	time_t el = now - g_LastFrame;
	if (el > 50) {
		g_LastFrame = now;
	}

	if (g_State == waiting_to_start)
	{
		if (!g_Keys[' '])
		{
			clearScreen();
			background_draw2(g_HomeBkg, g_HomeBkg->pos, v2i(0,0));
			//background_draw2(g_HomeBkg, g_HomeBkg->pos, v2i(0, 0) + v2i(c_ScreenW+separation, 0));
			/*for (int a = 0; a < (int)g_Entities.size(); a++) {
				if (g_Entities[a]->name == "player1" || g_Entities[a]->name == "player2")
				{
					entity_draw(g_Entities[a], g_viewpos1, 0);
					entity_draw(g_Entities[a], g_viewpos2, c_ScreenW + separation);
				}
			}*/

		}
		else
		{
			g_State = playing;
			g_Keys[' '] = false;
			play_sound(theme);

		}
	}

	else if (g_State == playing)
	{
		std::cerr << Console::red << theme << Console::gray << endl;
		if (now - g_Music > 150000){
			g_Music = now;
			play_sound(theme);
		}

		if (numFootContacts1 > 0) doubleJump1 = 0;
		if (numFootContacts2 > 0) doubleJump2 = 0;

		if (g_Keys[' '])
		{
			g_State = waiting_to_restart;
			g_Keys[' '] = false;

		}

		if (g_Player1->life == 0 || g_Player2->life == 0 || g_Player1->score == 3 || g_Player2->score == 3)
		{
			g_State = end_of_the_game;
		}

		//// Physics
		phy_step();

		//// Logic

		
		

		// -> step all entities
		for (int a = 0; a < (int)g_Entities.size(); a++) {
			entity_step(g_Entities[a], el);
		}

		

		g_viewpos1[0] = (int)entity_get_pos(g_Player1)[0] - c_ScreenW / 2;
		g_viewpos1[1] = (int)entity_get_pos(g_Player1)[1] - c_ScreenH / 2;
		g_viewpos2[0] = (int)entity_get_pos(g_Player2)[0] - c_ScreenW / 2;
		g_viewpos2[1] = (int)entity_get_pos(g_Player2)[1] - c_ScreenH / 2;

		// -> update viewpos (x coord only in this 'game')

		g_Bkg1->viewpos[0] = (int)entity_get_pos(g_Player1)[0];
		g_Bkg1->viewpos[1] = (int)entity_get_pos(g_Player1)[1];
		g_Bkg2->viewpos[0] = (int)entity_get_pos(g_Player2)[0];
		g_Bkg2->viewpos[1] = (int)entity_get_pos(g_Player2)[1];


		//// Display

		clearScreen();

		// -> draw background
		background_draw2(g_Bkg1, g_Bkg1->pos, v2i(-g_viewpos1[0] / 17.0, -g_viewpos1[1] / 25.0));
		background_draw2(g_Bkg2, g_Bkg2->pos, v2i(-g_viewpos2[0] / 17.0, -g_viewpos2[1] / 25.0) + v2i(c_ScreenW + separation + 100, 0));

		
		
		

		// -> draw tilemap
		tilemap_draw(g_Tilemap, g_viewpos1, 0);
		tilemap_draw(g_Tilemap, g_viewpos2, c_ScreenW + separation);

		g_Separation->draw(c_ScreenW + separation / 2 + 10 - g_Separation->w() / 2, 0 - 0 * g_Separation->h() / 2);

		// -> draw all entities
		
			
		entity_set_pos(g_Entities[whereIsTheStar], g_Stars2[five[g_Entities[whereIsTheStar]->nbOfStars]]);

		entity_set_pos(g_Entities[whereIsDiamond0], g_Gems2[twelve[g_Entities[whereIsDiamond0]->nbOfDiamonds]]);
		entity_set_pos(g_Entities[whereIsDiamond1], g_Gems2[twelve[g_Entities[whereIsDiamond1]->nbOfDiamonds + 4]]);
	

			
			
		
		
		for (int a = 0; a < (int)g_Entities.size(); a++) {
				entity_draw(g_Entities[a], g_viewpos1, 0);
				entity_draw(g_Entities[a], g_viewpos2, c_ScreenW + separation);
		}

		
		
		// -> draw physics debug layer
		//phy_debug_draw();
	}
	else if (g_State == waiting_to_restart)
	{
		if (!g_Keys[' '])
		{
			clearScreen();
			background_draw2(g_PauseBkg, g_PauseBkg->pos, v2i(0, 0));
		//	background_draw2(g_PauseBkg, g_PauseBkg->pos, v2i(0, 0) + v2i(c_ScreenW + separation/2, 0));

		}
		else
		{
			g_State = playing;
			g_Keys[' '] = false;
		    play_sound(theme);
		}
	}

	else if (g_State == end_of_the_game)
	{

		if (!g_Keys[' '] || !g_Keys['q'])
		{
			clearScreen();
			if (g_Player1->score == 3){
				g_EndBkg = background_init2(400, 400, 6, 6);
			}
			else if (g_Player2->score == 3){
				g_EndBkg = background_init2(400, 400, 7, 7);
			}
			background_draw2(g_EndBkg, g_EndBkg->pos, v2i(0, 0));
			g_Stars2.clear();
			g_Ennemies.clear();
			g_Stars.clear();
	
						
		}

		if (g_Keys[' '])
		{
			numFootContacts1 = 0;
			numLeftContacts1 = 0;
			numRightContacts1 = 0;
			numFootContacts2 = 0;
			numLeftContacts2 = 0;
			numRightContacts2 = 0;

			for (int i = 0; i < 8; i++){
				twelve[i] = -1;
			}

			{
				i = 0;
				r = 0;
				while (i < 8){
					r = rand() % 8;
					isInArray = std::find(std::begin(twelve), std::end(twelve), r) != std::end(twelve);
					while (isInArray){
						r = rand() % 8;
						isInArray = std::find(std::begin(twelve), std::end(twelve), r) != std::end(twelve);
					}
					twelve[i] = r;
					i++;
				}
			}

			for (int i = 0; i < 12; i++){
				five[i] = -1;
			}

			{
				i = 0;
				r = 0;
				while (i < 12){
					r = rand() % 12;
					isInArray = std::find(std::begin(five), std::end(five), r) != std::end(five);
					while (isInArray){
						r = rand() % 12;
						isInArray = std::find(std::begin(five), std::end(five), r) != std::end(five);
					}
					five[i] = r;
					i++;
				}
			}

			field = rand() % 4;
			while (field == lastField){
				field = rand() % 4;
			}
			lastField = field;
			
			g_Entities.clear();

			switch (field){
			case 0:
				monster = "monster_ice.lua";
				barrel_r = "barrel_ice_r.lua";
				barrel_l = "barrel_ice_l.lua";
				spikes = "spikes_ice.lua";
				level = "ice_level.lua";
				ball = "ice_ball.lua";
				g_Bkg1 = background_init2(c_ScreenW, c_ScreenH, 0, 2);
				g_Bkg2 = background_init2(c_ScreenW, c_ScreenH, 0, 2);
				break;
			case 1:
				monster = "monster_met.lua";
				barrel_r = "barrel_met_r.lua";
				barrel_l = "barrel_met_l.lua";
				spikes = "spikes_met.lua";
				level = "met_level.lua";
				ball = "met_ball.lua";
				g_Bkg1 = background_init2(c_ScreenW, c_ScreenH, 1, 2);
				g_Bkg2 = background_init2(c_ScreenW, c_ScreenH, 1, 2);

				break;
			case 2:
				monster = "monster_nat.lua";
				barrel_r = "barrel_nat_r.lua";
				barrel_l = "barrel_nat_l.lua";
				spikes = "spikes_nat.lua";
				level = "nat_level.lua";
				ball = "nat_ball.lua";
				g_Bkg1 = background_init2(c_ScreenW, c_ScreenH, 2, 2);
				g_Bkg2 = background_init2(c_ScreenW, c_ScreenH, 2, 2);

				break;
			case 3:
				monster = "monster_wood.lua";
				barrel_r = "barrel_wood_r.lua";
				barrel_l = "barrel_wood_l.lua";
				spikes = "spikes_wood.lua";
				level = "wood_level.lua";
				ball = "wood_ball.lua";
				g_Bkg1 = background_init2(c_ScreenW, c_ScreenH, 3, 2);
				g_Bkg2 = background_init2(c_ScreenW, c_ScreenH, 3, 2);

				break;
			}



			
			// terminate physics
			phy_terminate();

			// load a tilemap
			g_Tilemap = tilemap_load(level);

			// init physics
			phy_init();

			// bind tilemap to physics
			tilemap_bind_to_physics(g_Tilemap);

			theme = music[rand() % 6];

			{
				Entity *c = entity_create("player1", 1, "player1.lua");
				entity_set_pos(c, v2f(300, 1000));
				g_Player1 = c;
				g_Entities.push_back(c);


			} {
				Entity *c = entity_create("player2", 1, "player2.lua");
				entity_set_pos(c, v2f(2000, 1000));
				g_Player2 = c;
				g_Entities.push_back(c);
			} {
				for (int i = 0; i < g_Ennemies.size(); i++)
				{
					if (g_Ennemies[i][2] == 2){
						Entity *c = entity_create("monster", 2, monster);
						entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
						g_Entities.push_back(c);
					}

					else if (g_Ennemies[i][2] == 1){
						Entity *c = entity_create("crabs", 2, "crabs.lua");
						entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
						g_Entities.push_back(c);
					}

					else if (g_Ennemies[i][2] == 0){
						Entity *c = entity_create("fly", 2, "ennemy_fly.lua");
						entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
						g_Entities.push_back(c);
					}
					else if (g_Ennemies[i][2] == 3){
						Entity *c = entity_create("spikes", 2, spikes);
						entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
						g_Entities.push_back(c);
					}
					else if (g_Ennemies[i][2] == 4){
						
						Entity *c = entity_create("barrel", 6, barrel_r);
						entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
						g_Entities.push_back(c);
					}
					else if (g_Ennemies[i][2] == 5){
						
						Entity *c = entity_create("barrel", 6, barrel_l);
						entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
						g_Entities.push_back(c);
					}
					else {
						Entity *c = entity_create(to_string(i), 2, "ennemy.lua");
						entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
						c->movement = g_Ennemies[i][2];
						g_Entities.push_back(c);
					}
				}
			} {
				for (int i = 0; i < g_Stars.size(); i++){
					v2f c = v2f(g_Stars[i][0], g_Stars[i][1]);
					g_Stars2.push_back(c);
				}
			}

		


		{
			Entity *c = entity_create("star", 3, "star.lua");
			entity_set_pos(c, g_Stars2[five[c->nbOfStars]]);
			g_Entities.push_back(c);
			whereIsTheStar = g_Entities.size() - 1;
		}

		{
			for (int i = 0; i < 2; i++){
				Entity *c = entity_create(to_string(i), -1, "gemme.lua");
				entity_set_pos(c, g_Gems2[twelve[c->nbOfDiamonds + 4 * i]]);
				g_Entities.push_back(c);

			}
		}

		whereIsDiamond0 = g_Entities.size() - 2;
		whereIsDiamond1 = g_Entities.size() - 1;

		{
			for (int i = 0; i < 2; i++){
				Entity* c = entity_create("ball", 10 + i, ball);
				entity_set_pos(c, v2f(-100, -100));
				c->whoseCharacterIsThisBall = i;
				g_Entities.push_back(c);
			}
		}

		whereIsBall0 = g_Entities.size() - 2;
		whereIsBall1 = g_Entities.size() - 1;



			g_State = playing;
			play_sound(theme);

		}
		
		if (g_Keys['q']){
			
			SimpleUI::shutdown();
			exit(0);
		}


	}

	


}

// ------------------------------------------------------------------




// 'main' is the starting point of the application
int main(int argc, const char **argv)
{
	srand(time(0));
	
	
	try { // error handling
		

		// opens a window
		SimpleUI::init(c_ScreenW*ratio_split + separation, c_ScreenH, "Tilemap");
		// set the render function to be 'mainRender' defined above
		SimpleUI::onRender = mainRender;
		// set the keyboard function
		SimpleUI::onKeyPressed = mainKeyPressed;
		SimpleUI::onKeyUnpressed = mainKeyUnpressed;

		// init drawimage library
		drawimage_init(c_ScreenW*ratio_split + separation, c_ScreenH);



		// keys
		for (int i = 0; i < 256; i++) {
			g_Keys[i] = false;
		}

		g_State = waiting_to_start;

		///// Level creation

		// create background


		g_HomeBkg = background_init2(400, 274, 3, 3);
		g_PauseBkg = background_init2(400, 400, 4, 4);
		g_EndBkg = background_init2(400, 400, 5, 5);
		/*g_Bkg1 = background_init2(c_ScreenW, c_ScreenH, 0, 0);
		g_Bkg2 = background_init2(c_ScreenW, c_ScreenH, 0, 0);*/

		g_Separation = new DrawImage(executablePath()  + "/data/sprites/" + "bandeau2.jpg");
		i_0Score = new DrawImage(executablePath()  + "/data/" + "0.png");
		i_1Score = new DrawImage(executablePath()  + "/data/" + "1.png");
		i_2Score = new DrawImage(executablePath()  + "/data/" + "2.png");
		i_3Score = new DrawImage(executablePath()  + "/data/" + "3.png");
		// load a tilemap
		
		field = rand() % 4;
		lastField = field;
		theme = music[rand() % 6];
		
		switch (field){
		case 0:
			monster = "monster_ice.lua";
			barrel_r = "barrel_ice_r.lua";
			barrel_l = "barrel_ice_l.lua";
			spikes = "spikes_ice.lua";
			level = "ice_level.lua";
			ball = "ice_ball.lua";
			g_Bkg1 = background_init2(c_ScreenW, c_ScreenH, 0, 2);
			g_Bkg2 = background_init2(c_ScreenW, c_ScreenH, 0, 2);
			break;
		case 1:
			monster = "monster_met.lua";
			barrel_r = "barrel_met_r.lua";
			barrel_l = "barrel_met_l.lua";
			spikes = "spikes_met.lua";
			level = "met_level.lua";
			ball = "met_ball.lua";
			g_Bkg1 = background_init2(c_ScreenW, c_ScreenH, 1, 2);
			g_Bkg2 = background_init2(c_ScreenW, c_ScreenH, 1, 2);

			break;
		case 2:
			monster = "monster_nat.lua";
			barrel_r = "barrel_nat_r.lua";
			barrel_l = "barrel_nat_l.lua";
			spikes = "spikes_nat.lua";
			level = "nat_level.lua";
			ball = "nat_ball.lua";
			g_Bkg1 = background_init2(c_ScreenW, c_ScreenH, 2, 2);
			g_Bkg2 = background_init2(c_ScreenW, c_ScreenH, 2, 2);

			break;
		case 3:
			monster = "monster_wood.lua";
			barrel_r = "barrel_wood_r.lua";
			barrel_l = "barrel_wood_l.lua";
			spikes = "spikes_wood.lua";
			level = "wood_level.lua";
			ball = "wood_ball.lua";
			g_Bkg1 = background_init2(c_ScreenW, c_ScreenH, 3, 2);
			g_Bkg2 = background_init2(c_ScreenW, c_ScreenH, 3, 2);

			break;
		}

		g_Tilemap = tilemap_load(level);
		// init physics
		phy_init();

		// bind tilemap to physics
		tilemap_bind_to_physics(g_Tilemap);

		// load a simple entity
          {
			Entity *c = entity_create("player1", 1, "player1.lua");
			entity_set_pos(c, v2f(300, 1000));
			g_Player1 = c;
			g_Entities.push_back(c);


		} {
			Entity *c = entity_create("player2", 1, "player2.lua");
			entity_set_pos(c, v2f(2000, 1000));
			g_Player2 = c;
			g_Entities.push_back(c);
		  } {
			for (int i = 0; i < g_Gems.size(); i++){
				v2f c = v2f(g_Gems[i][0], g_Gems[i][1]);
				g_Gems2.push_back(c);
			}
		}

		{
			i = 0;
			r = 0;
			while (i < 8){
				r = rand() % 8;
				isInArray = std::find(std::begin(twelve), std::end(twelve), r) != std::end(twelve);
				while (isInArray){
					r = rand() % 8;
					isInArray = std::find(std::begin(twelve), std::end(twelve), r) != std::end(twelve);
				}
				twelve[i] = r;
				i++;
			}
		}

		{
			for (int i = 0; i < 2; i++){
				Entity *c = entity_create(to_string(i), -1, "gemme.lua");
				entity_set_pos(c, g_Gems2[twelve[c->nbOfDiamonds + 4 * i]]);
				g_Entities.push_back(c);

			}
		}

		whereIsDiamond0 = g_Entities.size() - 2;
		whereIsDiamond1 = g_Entities.size() - 1;


		  {
			for (int i = 0; i < g_Ennemies.size(); i++)
			{
				if (g_Ennemies[i][2]==2){
				Entity *c = entity_create(to_string(i), 2, monster);
				entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
				g_Entities.push_back(c);
				}

				else if (g_Ennemies[i][2] == 1){
					Entity *c = entity_create("crabs", 2, "crabs.lua");
					entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
					g_Entities.push_back(c);
				} 
				
				else if (g_Ennemies[i][2] == 0){
					Entity *c = entity_create("fly", 2, "ennemy_fly.lua");
					entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
					g_Entities.push_back(c);
				}
				else if (g_Ennemies[i][2] == 3){
					Entity *c = entity_create("spikes", 2, spikes);
					entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
					g_Entities.push_back(c);
				}
				else if (g_Ennemies[i][2] == 4){
					
					Entity *c = entity_create("barrel", 6, barrel_r);
					entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
					g_Entities.push_back(c);
				}
				else if (g_Ennemies[i][2] == 5){
				
					Entity *c = entity_create("barrel", 6, barrel_l);
					entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
					g_Entities.push_back(c);
				}
				else {
					Entity *c = entity_create(to_string(i), 2, "ennemy.lua");
					entity_set_pos(c, v2f(g_Ennemies[i][0], g_Ennemies[i][1]));
					c->movement = g_Ennemies[i][2];
					g_Entities.push_back(c);
				}
			}
		} {
			for (int i = 0; i < g_Stars.size(); i++){
				v2f c = v2f(g_Stars[i][0], g_Stars[i][1]);
				g_Stars2.push_back(c);
			}
		}
	
		{
			i = 0;
			r = 0;
			while (i < 12){
				r = rand() % 12;
				isInArray = std::find(std::begin(five), std::end(five), r) != std::end(five);
				while (isInArray){
					r = rand() % 12;
					isInArray = std::find(std::begin(five), std::end(five), r) != std::end(five);
				}
				five[i] = r;
				i++;
			}
		}


		{
			Entity *c = entity_create("star", 3, "star.lua");
			entity_set_pos(c, g_Stars2[five[c->nbOfStars]]);
			g_Entities.push_back(c);
			whereIsTheStar = g_Entities.size() - 1;
		}

		{
			for (int i = 0; i < 2; i++){
				Entity* c = entity_create("ball", 10 + i, ball);
				entity_set_pos(c, v2f(-100, -100));
				c->whoseCharacterIsThisBall = i;
				g_Entities.push_back(c);
			}
		}

		whereIsBall0 = g_Entities.size() - 2;
		whereIsBall1 = g_Entities.size() - 1;


		g_LastFrame = milliseconds();
		g_Music = milliseconds();



		init_sound();
		// enter the main loop
		SimpleUI::loop();

		// terminate physics
		phy_terminate();
		// terminate drawimage
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
