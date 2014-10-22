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
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
int lvl2[TILEY][TILEX] = {
		/*Level 2*/
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
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
	curLvl = 1;
	LoadLvl(curLvl);
}

//Load level and spawn elements in the level
//Basically the most important function here
void LoadLvl(int curLevel){
	Sprite *sprite;
	Entity *ent;
	int test;
	col = 0;
	printf("%d",lvl1[2][3]);
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
		printf("\n");
		for(j = 0; j < TILEX; j++){
			if(curLevel == 1){
				test = lvl1[i][j];
			}else if(curLevel == 2){
				test = lvl2[i][j];
			}else if(curLevel ==3){
				test = lvl3[i][j];
			}
			if(test == 1){
				sprite = LoadSprite("images/redPlay.png",32,32);
				ent = CreateChar(j*32,i*32,sprite,M_RED);
				DrawSprite(ent->sprite,buffer,ent->x,ent->y,0);
			}else if(test == 2){
				sprite = LoadSprite("images/bluePlay.png",32,32);
				ent = CreateChar(j*32,i*32,sprite,M_BLUE);
				DrawSprite(ent->sprite,buffer,ent->x,ent->y,0);
			}else if(test == 3){
				sprite = LoadSprite("images/purpBlock.png",32,32);
				ent = CreateBlock(j*32,i*32,sprite,M_PURP);
				printf("%d", ent->x);
				DrawSprite(ent->sprite,buffer,ent->x,ent->y,0);
			}else if(test == 4){
				sprite = LoadSprite("images/redBlock.png",32,32);
				ent = CreateBlock(j*32,i*32,sprite,M_RED);
				DrawSprite(ent->sprite,buffer,ent->x,ent->y,0);
			}else if(test == 5){
				sprite = LoadSprite("images/blueBlock.png",32,32);
				ent = CreateBlock(j*32,i*32,sprite,M_BLUE);
				DrawSprite(ent->sprite,buffer,ent->x,ent->y,0);
			}else if(test == 6){
				sprite = LoadSprite("images/redHaz.png",32,32);
				ent = CreateOb(j*32,i*32,sprite,M_RED);
				DrawSprite(ent->sprite,buffer,ent->x,ent->y+16,0);
			}else if(test == 7){
				sprite = LoadSprite("images/blueHaz.png",32,32);
				ent = CreateOb(j*32,i*32,sprite,M_BLUE);
				DrawSprite(ent->sprite,buffer,ent->x,ent->y+26,0);
			}else if(test == 8){
				sprite = LoadSprite("images/purpFinish.png",32,32);
				ent = CreateGoal(j*32,i*32);
				DrawSprite(ent->sprite,buffer,ent->x,ent->y,0);
			}
		}
	}
}

//Use if both player characters over goal
void NextLevel(int curLevel){
	curLvl++;
	LoadLvl(curLevel);
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
