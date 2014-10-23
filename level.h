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

#include "SDL.h"


void InitLvl();
void LoadLvl(int curLevel);
void NextLevel(int curLevel);
void BackLevel(int curLevel);
void ReloadLevel(int curLevel);
void ClearLvl();
#endif