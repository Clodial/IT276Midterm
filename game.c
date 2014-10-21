#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;

void Init_All();


/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
  int done;
  int keyn;
  Uint8 *keys;
  Init_All();
 
  done = 0;
  do
  {
    ResetBuffer();
    DrawMouse();
    NextFrame();
	//DrawLvl();
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

  InitMouse();
  atexit(CleanUpAll);
}

