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
extern Entity EntList[MAXENTITIES];
int i,j;
int curLvl;
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
int lvl1[TILEY][TILEX] ={
		/*Level 1*/
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,1,0,0,7,0,0,0,0,0,0,0},
	{0,0,0,0,2,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
int lvl2[TILEY][TILEX] = {
		/*Level 2*/
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,5,0,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
int lvl3[TILEY][TILEX]={
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
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};



//establish what is the first level while loading said level
void InitLvl(){
	curLvl = 1; /*Set the current level*/
	LoadLvl(curLvl);
}

//Load level and spawn elements in the level
//Basically the most important function here
void LoadLvl(int curLevel){
	int num;
	SDL_Rect chBox;
	Sprite *sprite;
	Entity *ent;
	int maps[TILEY][TILEX];

	chBox.h = 32;
	chBox.w = 32;

	if(curLevel == 1){
		memcpy(maps,lvl1,sizeof(lvl1));
	}else if(curLevel == 2){
		memcpy(maps,lvl2,sizeof(lvl2));
	}else if(curLevel ==3){
		memcpy(maps,lvl3,sizeof(lvl3));
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
				printf("initial: %x\n",sprite);
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

//Use if both player characters over goal
void NextLevel(int curLevel){
	if(curLvl < 3){
		curLvl++;
		ClearLvl();
		LoadLvl(curLevel);
	}
}

//
void BackLevel(int curLevel){
	if(curLvl > 1){
		ClearLvl();
		curLvl--;
		LoadLvl(curLevel);
	}
}
//Use if player presses R or click a reload option
void ReloadLevel(int curLevel){
	ClearLvl();
	LoadLvl(curLevel);
}

//Clear out all assets in the level (Mostly for when reloading a level
//or going to the next level)
void ClearLvl(){
	ClearAllEnt();
}
