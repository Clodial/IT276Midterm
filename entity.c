/*****
*
*	entity.c
*
*****/
#include "entity.h"
#include <stdlib.h>
#include <math.h>
#include "SDL.h"
#include "level.h"

SDL_Event Event;

Entity EntList[MAXENTITIES];
int numEnts;
extern SDL_Surface *screen;
extern int curLvl;
Entity *redChar;
Entity *blueChar;
int inAir;

/*Main functions for initializing*/
void InitEnt(){
	int i;
	numEnts = 0; /*If this wasn't 0, well, then there would be a problem*/
	for(i = 0; i < MAXENTITIES; i++){
		EntList[i].sprite = NULL;
		EntList[i].think = NULL;
		EntList[i].used = 0;
	}
}
Entity *NewEnt(){
	int i;
	if(numEnts + 1 >= MAXENTITIES){
		return NULL;
	}
	numEnts++;
	/*establish memory for new entity*/
	for(i = 0;i <= numEnts; i++){
		if(EntList[i].used == 0)break;
	}
	EntList[i].used = 1;
	return &EntList[i];
}
void DrawEnts(){
	int i;
	for(i = 0; i < MAXENTITIES;i++){
		if(EntList[i].used){
	        DrawEnt(&EntList[i]);
	    }
	}
}
void DrawEnt(Entity *ent){
	/*Frame set to 0 for testing purposes*/
	DrawSprite(ent->sprite,screen,ent->x,ent->y,0);
}
void UpdateEnt(){
	int i;
	for(i = 0; i < MAXENTITIES; i++){
		if(EntList[i].used){
			if(EntList[i].think != NULL){
				EntList[i].think(&EntList[i]);
			}
		}
	}
}

/*Cleanup for entities*/
void DestEnt(Entity *ent){
	/*remove a single entity from memory*/
	ent->used = 0;
	numEnts--;
	if(ent->sprite != NULL){
		printf("checked if sprite was here \n");
		FreeSprite(ent->sprite);
	}
	ent->sprite = NULL;
}
void ClearAllEnt(){
	int i;
	for(i = 0;i < MAXENTITIES; i++){
		DestEnt(&EntList[i]);
	}
}


Entity *CreateChar(int x, int y, Sprite *s, int m){
	Entity *player;
	player = NewEnt();
	if(player == NULL)return player;
	player->solid = 1;
	player->sprite = s;
	player->mode = m;
	player->x = x;
	player->y = y;
	player->w = 32;
	player->h = 32;
	player->think = CharThink;
	player->frame = 0;
	if(redChar != NULL){
		player->active = 0; 
		blueChar = player;
	}else{
		player->active = 1;
		redChar = player;
	}
	return player;
}
void CharThink(Entity *self){
	int keyn;
	Uint8 *keys;
	self->x += self->vx;
	//printf("%d\n",self->x);
	//printf("%d\n",self->sx);
	//DrawEnt(self);
	if(self->x > 672 || self->x < -32 || self->y > 480){
		ReloadLevel(curLvl);
	}
	while(SDL_PollEvent(&Event)){
		switch(Event.type){
			case SDL_KEYDOWN:
				switch(Event.key.keysym.sym){
					case SDLK_RIGHT:
						self->vx = 2;
						//printf("%d\n",self->x);
						//printf("%d\n",self->sx);
						break;
					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch(Event.key.keysym.sym){
					case SDLK_RIGHT:
							self->vx = 0;
							break;
					default:
						break;
				}
				break;
		}
	}
}

Entity *CreateBlock(int x, int y, Sprite *s, int m){
	Entity *block;
	block = NewEnt();
	if(block == NULL) return block;
	block->used = 1;
	block->solid = 1;
	block->sprite = s;
	block->mode = m;
	block->x = x;
	block->y = y;
	block->w = 32;
	block->h = 32;
	block->frame = 0;
	return block;
}
void BlockThink(Entity *self){
	/*make sure the player can move/finish up*/
}

Entity *CreateOb(int x, int y, Sprite *s, int m){
	Entity *obstacle;
	obstacle = NewEnt();
	if(obstacle == NULL) return obstacle;
	obstacle->used = 1;
	obstacle->solid = 1;
	obstacle->sprite = s;
	obstacle->mode = m;
	obstacle->x = x;
	obstacle->y = y;
	obstacle->w = 32;
	obstacle->h = 16;
	obstacle->frame = 0;
	return obstacle;
}
void ObThink(Entity *self){
	/*check for collision between itself and a character*/
}

Entity *CreateGoal(int x, int y){
	Entity *goal;
	goal = NewEnt();
	if(goal == NULL) return goal;
	goal->used = 1;
	goal->solid = 1;
	goal->sprite = LoadSprite("images/purpFinish.png",0,0);
	goal->mode = M_PURP;
	goal->x = x;
	goal->y = y;
	goal->w = 32;
	goal->h = 32;
	goal->frame = 0;
	return goal;
}
void GoalThink(Entity *self){
	/*Check if redChar and blueChar are ontop of it*/
}

void jump(Entity *character){

}
