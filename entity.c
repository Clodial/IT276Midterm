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

#define GRAVITY 1

SDL_Event Event;

Entity EntList[MAXENTITIES];
int numEnts;
extern SDL_Surface *screen;
extern int curLvl;
extern int col;
extern int *maps[TILEY][TILEX];
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
	player->vy = 0.0f;
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
	if(self->active == 1){
		self->y = self->y + (int)self->vy;
	}
	if(self->active == 1 && self->air == 1){
		if(self->vy < MAX_FALL){
			self->vy = self->vy + GRAVITY; 
		}else{
			self->vy = MAX_FALL;
		}
	}
	if(self->x > 672 || self->x < -32 || self->y > 480){
		SDL_Delay(2000);
		ReloadLevel(curLvl);
	}//Meant to reload level upon defeat
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
	obstacle->think = ObThink;
	obstacle->frame = 0;
	return obstacle;
}
void ObThink(Entity *self){
	/*check for collision between itself and a character*/
	if(BoxCollide(self,blueChar) == 1){
		SDL_Delay(200);
		ReloadLevel(curLvl);
	}
	if(BoxCollide(self, redChar) == 1){
		SDL_Delay(200);
		ReloadLevel(curLvl);
	}
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

void Input(){
	int keyn;
	Uint8 *keys;

	while(SDL_PollEvent(&Event)){
		switch(Event.type){
			case SDL_KEYUP:
				switch(Event.key.keysym.sym){
					case SDLK_SPACE:
						if(blueChar->air == 0 && redChar->air == 0){
							if(col == 0){
								redChar->active = 1;
								blueChar->active = 0;
								col = 1;
							}else{ 
								blueChar->active = 1;
								redChar->active = 0;
								col = 0;
							}
						}
						break;
				}
				break;
		}
		break;
	}
	SDL_PumpEvents();
	keys = SDL_GetKeyState(&keyn);
	if(keys[SDLK_UP]){
		if(col == 1){
			if(redChar->air == 0){
				redChar->vy = VY;
				redChar->air = 1;
			}
		}else{
			if(blueChar->air == 0){
				blueChar->vy = VY;

				blueChar->air = 1;
			}
		}
	}
	if(keys[SDLK_RIGHT]){
		if(col == 1){
			if(PlaceFree(redChar,redChar->x+redChar->w,redChar->y) == 1){
				redChar->x += (int)VX;
			}
		}
		else{
			if(PlaceFree(blueChar,blueChar->x+blueChar->w,blueChar->y) == 1){
				blueChar->x += (int)VX;
			}
		}
	}
	if(keys[SDLK_LEFT]){
		if(col == 1){
			if(PlaceFree(redChar, (redChar->x),redChar->y) == 1){
				redChar->x -= (int)VX;
			}
		}
		else{
			if(PlaceFree(blueChar,(blueChar->x),blueChar->y) == 1){
				blueChar->x -= (int)VX;
			}
		}
	}
}

//function to check if place moving to is free
int PlaceFree(Entity *ent, int x, int y){
	int cx,cy;
	int cx2,cy2; //in case the destination is an exact position
	cx = x / 32; //get the tile that is there
	cy = y / 32;
	cx2 = x % 32;
	cy2 = y % 32;
	printf("%d\n",cx2);
	printf("%d\n",cy2);
	if(ent->mode == M_RED){
		if((maps[cy][cx] == 8 || maps[cy][cx] == 4 || maps[cy][cx] == 3) && (cx2 == 0 && cy2 == 0)){
			return 0; // basically saying that the tile desired is not free
		}
	}else{
		if((maps[cy][cx] == 8 || maps[cy][cx] == 5 || maps[cy][cx] == 3) && (cx2 == 0 && cy2 == 0)){
			return 0; // basically saying that the tile desired is not free
		}
	}
	return 1;
}

//Function to check if the current character will collide with the other character
int OtherPlayer(Entity *self, Entity *tar, int vx, int vy){
	return 0;
}
int BoxCollide(Entity *self, Entity *targ){
    if( self->x+self->w < targ->x || self->x > targ->x+targ->w ) return 0;
    if( self->y+self->h < targ->y || self->y > targ->y+targ->h ) return 0;
	return 1;
}