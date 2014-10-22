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
extern int inAir; /*This is to make sure that a player can change the background all willy nilly*/
extern int curLvl;
/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
  SDL_Surface *temp;
  SDL_Surface *bg;
  int done;
  int keyn;
  int mx,my;
  int tCol;
  Uint8 *keys;
  Init_All();
  col = 0;
  temp = IMG_Load("images/redBack.png");
  inAir = 1; /*This is something that will be determined based on if a character is in air*/
  if(temp != NULL){
	bg = SDL_DisplayFormat(temp);
  }
  SDL_FreeSurface(temp);
  if(bg != NULL){
	SDL_BlitSurface(bg,NULL,buffer,NULL);
  }
  InitLvl();
  done = 0;
  do
  {
    ResetBuffer();
    NextFrame();
	UpdateEnt();
	DrawEnts();
    SDL_PumpEvents();
    keys = SDL_GetKeyState(&keyn);
	tCol = col; /*Change state of background*/
	if(tCol == 0){
		temp = IMG_Load("images/blueBack.png");
	}else{
		temp = IMG_Load("images/redBack.png");
	}
	if(keys[SDLK_SPACE] && inAir == 0){
		if(tCol == 0){
			temp = IMG_Load("images/blueBack.png");
			printf("blue");
			tCol = 1;
		}else{
			temp = IMG_Load("images/redBack.png");
			printf("red");
			tCol = 0;
		}
		if(temp != NULL){
			bg = SDL_DisplayFormat(temp);
		}
		SDL_FreeSurface(temp);
		if(bg != NULL){
			SDL_BlitSurface(bg,NULL,buffer,NULL);
		}
		SDL_Delay(200);
	}
	if(keys[SDLK_r]){
		ReloadLevel(curLvl);
		SDL_Delay(200);
	}
	col = tCol;
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

void Init_All()
{
  Init_Graphics();
  InitMouse();
  atexit(CleanUpAll);
}
