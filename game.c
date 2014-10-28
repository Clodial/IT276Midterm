#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "level.h"
#include "entity.h"

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;

void Init_All();
extern int col; /*Change state of the level*/
extern int curLvl;
extern int rep;
extern int forw;
extern int backw;
extern int numEnts;

extern Entity *redChar;//I need to take off their pointers upon reload
extern Entity *blueChar;
SDL_Event Event;
/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
  SDL_Surface *temp;
  SDL_Surface *bg;
  int done;
  int keyn;
  int tCol;
  int i;
  int ci;
  Uint8 *keys;

  Init_Graphics();
  col = 0;
  temp = IMG_Load("images/redBack.png");
  if(temp != NULL){
	bg = SDL_DisplayFormat(temp);
  }
  SDL_FreeSurface(temp);
  if(bg != NULL){
	SDL_BlitSurface(bg,NULL,buffer,NULL);
  }
  done = 0;
  Init_All();
  do
  {
	UpdateEnt();
	if(rep == 1){
		SDL_Delay(200);
		ClearAllEnt();
		redChar = NULL; //SO THAT GRAVITY CAN WORK ON THEM
		blueChar = NULL;
		LoadLvl(curLvl);
	}
	if(forw == 1){
		SDL_Delay(200);
		ClearAllEnt();
		redChar = NULL;
		blueChar = NULL;
		if(curLvl < MAXLEVELS){
			curLvl++;
		}
		LoadLvl(curLvl);
	}
	Input();
	tCol = col; /*Change state of background*/
    SDL_PumpEvents();
	keys = SDL_GetKeyState(&keyn);
	col = tCol;
	if(keys[SDLK_r]){
		rep = 1;
	}
    ResetBuffer();
	//level sprite changing things
	if(col == 0){
		temp = IMG_Load("images/blueBack.png");
	}else{
		temp = IMG_Load("images/redBack.png");
	}
	if(temp != NULL){
		bg = SDL_DisplayFormat(temp);
	}
	SDL_FreeSurface(temp);
	if(bg != NULL){
		SDL_BlitSurface(bg,NULL,buffer,NULL);
	}
	DrawEnts();
	NextFrame();
	if(keys[SDLK_ESCAPE])done = 1;
  }while(!done);
  exit(0);		/*technically this will end the program, but the compiler likes all functions that can return a value TO return a value*/
  return 0;
}

void CleanUpAll()
{
	CloseSprites();
	/*any other cleanup functions can be added here*/ 
}

void Init_All(){
	InitEnt();
	InitLvl();
	InitMouse();
	atexit(CleanUpAll);
}
