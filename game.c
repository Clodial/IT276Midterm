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


/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
  SDL_Surface *temp;
  SDL_Surface *bg;
  int done;
  int keyn;
  int mx,my;
  Uint8 *keys;
  Init_All();
  temp = IMG_Load("images/blueBack.png");
  if(temp != NULL){
	bg = SDL_DisplayFormat(temp);
  }
  SDL_FreeSurface(temp);
  done = 0;
  do
  {
    ResetBuffer();
    DrawMouse();
    NextFrame();
    SDL_PumpEvents();
    keys = SDL_GetKeyState(&keyn);
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

