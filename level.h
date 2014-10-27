#ifndef  _LEVEL_
#define _LEVEL_

/*
*
*	Level set up header file
*	-Basically use as a set-up
*
*/
#define TILEH 32
#define TILEW 32
#define TILEX 20
#define TILEY 15
#define MAXLEVELS 3

#include "SDL.h"

void CreateLevelList();
void CreateLevel(int *lvl[TILEY][TILEX]);
void InitLvl();
void LoadLvl(int c);
#endif