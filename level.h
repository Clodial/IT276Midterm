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

typedef struct LVL{
	int	number;	//level number
	int level[TILEX][TILEY]; //the tiles going into a level
}Level;

void LoadLvl();
void RendLvl(Level *lvl);
void SpawnLvlEnt(Level *lvl);
Level *GetCurLvl(int lNum);
void NextLevel(Level *lvl);
void ReloadLevel(Level *lvl);

#endif