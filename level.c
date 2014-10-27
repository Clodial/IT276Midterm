/******
*
*	level code
*
******/

#include <stdlib.h>
#include "level.h"
#include "entity.h"

extern SDL_Rect camera;
extern SDL_Surface *buffer;
extern int col;
extern Entity *EntList[MAXENTITIES];
extern Entity *redChar;
extern Entity *blueChar;
int LvlredF;
int LvlblueF;
int *maps[TILEY][TILEX];
int i,j;
int curLvl;
int backw;
int forw;
int rep;

	/*******
	*
	*	Level Value Denominators
	*	1 = red Character
	*	2 = blue Character
	*	3 = purple Block
	*	4 = red Block
	*	5 = blue Block
	*	6 = red Obstacle
	*	7 = blue Obstacle
	*	8 = purple Goal
	*
	*******/

int *tile1[TILEY][TILEX] ={

		/*Level 1*/

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,1,0,0,7,0,0,0,0,0,0,0},
	{0,0,0,0,2,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0},
	{0,0,0,0,4,4,3,3,5,5,3,3,3,3,3,3,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

};
int *tile2[TILEY][TILEX] = {

		/*Level 2*/

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,5,0,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

};
int *tile3[TILEY][TILEX]={

		/*Level 3*/

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,4,3,3,3,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

};
//establish what is the first level while loading said level
void InitLvl(){
	curLvl = 0; /*Set the current level*/
	LoadLvl(curLvl);
}

//Load level and spawn elements in the level
//Basically the most important function here
void LoadLvl(int curLevel){
	SDL_Rect chBox;
	Sprite *sprite;
	Entity *ent;

	rep = 0; // make sure the level doesn't keep repeating itself

	chBox.h = 32;
	chBox.w = 32;

	if(curLevel == 0){
		memcpy(maps,*tile1,sizeof(tile1));
	}else if(curLevel == 1){
		memcpy(maps,*tile2,sizeof(tile2));
	}else if(curLevel == 2){
		memcpy(maps,*tile3,sizeof(tile3));
	}else{
		memcpy(maps,*tile1,sizeof(tile1));
	}

	col = 1; /*Dye the level red*/
	//Leave some room for extra levels
	/*******
	*
	*	Level Value Denominators
	*	1 = red Character
	*	2 = blue Character
	*	3 = purple Block
	*	4 = red Block
	*	5 = blue Block
	*	6 = red Obstacle
	*	7 = blue Obstacle
	*	8 = purple Goal
	*
	*******/
	for(i = 0; i < TILEY; i++){
		for(j = 0; j < TILEX; j++){
			if(maps[i][j] == 1){
				sprite = LoadSprite("images/redPlay.png",32,32);
				ent = CreateChar(j*32,i*32,sprite,M_RED);
				//DrawSprite(ent->sprite,buffer,ent->x,ent->y,0);
			}else if(maps[i][j] == 2){
				sprite = LoadSprite("images/bluePlay.png",32,32);
				ent = CreateChar(j*32,i*32,sprite,M_BLUE);
				//DrawSprite(ent->sprite,buffer,ent->x,ent->y,0);
			}else if(maps[i][j] == 3){
				sprite = LoadSprite("images/purpBlock.png",32,32);
				ent = CreateBlock(j*32,i*32,sprite,M_PURP);
				//DrawSprite(ent->sprite,buffer,ent->x,ent->y,0);
			}else if(maps[i][j] == 4){
				sprite = LoadSprite("images/redBlock.png",32,32);
				ent = CreateBlock(j*32,i*32,sprite,M_RED);
				//DrawSprite(ent->sprite,buffer,ent->x,ent->y,0);
			}else if(maps[i][j] == 5){
				sprite = LoadSprite("images/blueBlock.png",32,32);
				ent = CreateBlock(j*32,i*32,sprite,M_BLUE);
				//DrawSprite(ent->sprite,buffer,ent->x,ent->y,0);
			}else if(maps[i][j] == 6){
				sprite = LoadSprite("images/redHaz.png",32,32);
				ent = CreateOb(j*32,i*32+16,sprite,M_RED);
				//DrawSprite(ent->sprite,buffer,ent->x,ent->y+16,0);
			}else if(maps[i][j] == 7){
				sprite = LoadSprite("images/blueHaz.png",32,32);
				ent = CreateOb(j*32,i*32+16,sprite,M_BLUE);
				//DrawSprite(ent->sprite,buffer,ent->x,ent->y+26,0);
			}else if(maps[i][j] == 8){
				sprite = LoadSprite("images/purpFinish.png",32,32);
				ent = CreateGoal(j*32,i*32);
				//DrawSprite(ent->sprite,buffer,ent->x,ent->y,0);
			}
		}
	}
}