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
int col;

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
  if(temp != NULL){
	bg = SDL_DisplayFormat(temp);
  }
  SDL_FreeSurface(temp);
  if(bg != NULL){
	SDL_BlitSurface(bg,NULL,buffer,NULL);
  }
  done = 0;
  do
  {
    ResetBuffer();
    NextFrame();
    SDL_PumpEvents();
    keys = SDL_GetKeyState(&keyn);
	tCol = col;
	if(keys[SDLK_SPACE]){
		if(tCol == 1){
			temp = IMG_Load("images/blueBack.png");
			printf("blue");
			tCol = 0;
		}else{
			temp = IMG_Load("images/redBack.png");
			printf("red");
			tCol = 1;
		}
		if(temp != NULL){
			bg = SDL_DisplayFormat(temp);
		}
		SDL_FreeSurface(temp);
		if(bg != NULL){
			SDL_BlitSurface(bg,NULL,buffer,NULL);
		}
		SDL_Delay(120);
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
  //InitLvl();
  InitMouse();
  atexit(CleanUpAll);
}
