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
extern int LvlredF;
extern int LvlblueF;
extern int rep;
extern int forw;
extern int backw;
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
		if(EntList[i].used != 0){ //I HATE THIS LINE OF CODE, BLAAAAAGH, COULD HAVE HANDED THIS GAME IN A LOT EARLIER IF I FIGURED THIS LINE OUT
								  // -.- Well, this happened regardless... uhm... yeah... let's make sure I'm not deleting images that were never there
			DestEnt(&EntList[i]);
		}
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
	printf("created player\n");
	return player;
}

void CharThink(Entity *self){
	Entity *targ;
	if(self == redChar){
		targ = blueChar;
	}else{
		targ = redChar;
	}
	//check if player is in the air
	if(self->active == 1){
		printf("PLAYER IS ACTIVE AND SHOULD BE FALLING\n");
		if(self->vy < MAX_FALL){
			self->vy = self->vy + GRAVITY; 
		}else{
			self->vy = MAX_FALL;
		}
		if(self->vy < 0.0){//Allow the player to go in the air
			if(self->vy > 0.0f && PlaceFree(self,self->x,self->y+(int)self->vy) == 0 && OtherPlayer(self,targ,self->x,self->y+(int)self->vy) == 0){
				self->vy = 0.0f; //stop character from colliding into block
			}
			self->y += (int)self->vy;
		}else if(PlaceFree(self,self->x,self->y+1) == 1 && OtherPlayer(self,targ,self->x,self->y+1) == 0){
			self->y += (int)self->vy;
		}else{
			self->vy = 0;
			self->air = 0;
		}
		//self->y = self->y + (int)self->vy;
	}else if(self->active == 0){
		if(BoxCollide(self,targ)){
			if(targ->y > self->y);
			targ->y = self->y - 32;
			targ->air = 0;
		}
	}
	if(self->x > 672 || self->x < -32 || self->y > 480){
		rep = 1;
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
	block->think = BlockThink;
	block->frame = 0;
	return block;
}
void BlockThink(Entity *self){
	/*fix up those nasty collision problems*/
	if(BoxCollide(self,redChar) == 1 && (self->mode == M_PURP || self->mode == M_RED)){
		if(redChar->y < self->y)
		redChar->y = self->y - 32;
		//LvlredF = 1;
	}else{LvlredF = 0;}
	if(BoxCollide(self,blueChar) == 1 && (self->mode == M_PURP || self->mode == M_BLUE)){
		if(blueChar->y < self->y)
		blueChar->y = self->y - 32;
		//LvlblueF = 1;
	}else{LvlblueF = 1;}

	if(LvlblueF == 1 && LvlredF == 1){
		forw = 1;
	}
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
	if(BoxCollide(self,blueChar) == 1 && self->mode == M_BLUE){
		rep = 1;
	}
	if(BoxCollide(self, redChar) == 1 && self->mode == M_RED){
		rep = 1;
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
	goal->think = GoalThink;
	goal->frame = 0;
	return goal;
}
void GoalThink(Entity *self){
	/*Check if redChar and blueChar are ontop of it*/
	if(BoxCollide(self,redChar) == 1){
		if(redChar->y < self->y)
		redChar->y = self->y - 32;
	}
	if(BoxCollide(self,blueChar) == 1){
		if(blueChar->y < self->y)
		blueChar->y = self->y - 32;
	}
}

void Input(){
	int keyn;
	Uint8 *keys;

	while(SDL_PollEvent(&Event)){
		switch(Event.type){
			case SDL_KEYUP:
				switch(Event.key.keysym.sym){
					case SDLK_SPACE:
						printf("pressed space \n");
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
	if(keys[SDLK_UP] && BoxCollide(redChar,blueChar) == 0){
		if(col == 1){
			if(redChar->air == 0){
				redChar->air = 1;
				redChar->vy = VY;
			}
		}else{
			if(blueChar->air == 0){
				blueChar->air = 1;
				blueChar->vy = VY;
			}
		}
	}
	if(keys[SDLK_RIGHT]){
		if(col == 1){
			if(PlaceFree(redChar,redChar->x+(int)VX,redChar->y) == 1 && OtherPlayer(redChar,blueChar, 1,0) == 0){
				redChar->x += (int)VX;
			}
		}
		else{
			if(PlaceFree(blueChar,blueChar->x+(int)VX,blueChar->y) == 1 && OtherPlayer(blueChar, redChar,1,0) == 0){
				blueChar->x += (int)VX;
			}
		}
	}
	if(keys[SDLK_LEFT]){
		if(col == 1){
			if(PlaceFree(redChar, (redChar->x-(int)VX),redChar->y) == 1 && OtherPlayer(redChar,blueChar,-1,0) == 0){
				redChar->x -= (int)VX;
			}
		}
		else{
			if(PlaceFree(blueChar,(blueChar->x-(int)VX),blueChar->y) == 1 && OtherPlayer(blueChar,redChar,-1,0) == 0){
				blueChar->x -= (int)VX;
			}
		}
	}
}

//function to check if place moving to is free
int PlaceFree(Entity *ent, int x, int y){
	int cx,cy; 
	int cx2,cy2; //to check the full length
	cx = x / 32; //get the tile that is there
	cy = y / 32;
	cx2 = (x + 31)/32;
	cy2 = (y + 31)/32;

	if(ent->mode == M_RED){
		if((maps[cy][cx] == 8 || maps[cy][cx] == 4 || maps[cy][cx] == 3) || (maps[cy][cx2] == 8 || maps[cy][cx2] == 4 || maps[cy][cx2] == 3) || (maps[cy2][cx] == 8 || maps[cy2][cx] == 4 || maps[cy2][cx] == 3) || (maps[cy2][cx2] == 8 || maps[cy2][cx2] == 4 || maps[cy2][cx2] == 3)){
			return 0; // basically saying that the tile desired is not free
		}
	}else if(ent->mode == M_BLUE){
		if((maps[cy][cx] == 8 || maps[cy][cx] == 5 || maps[cy][cx] == 3) || (maps[cy][cx2] == 8 || maps[cy][cx2] == 5 || maps[cy][cx2] == 3) || (maps[cy2][cx] == 8 || maps[cy2][cx] == 5 || maps[cy2][cx] == 3) || (maps[cy2][cx2] == 8 || maps[cy2][cx2] == 5 || maps[cy2][cx2] == 3)){
			return 0; // basically saying that the tile desired is not free
		}
	}
	return 1;
}

//Function to check if the current character will collide with the other character
int OtherPlayer(Entity *self, Entity *targ, int vx, int vy){
	if( self->x+vx < targ->x || self->x + vx > targ->x+targ->h) return 0; // there is no collision in that spot
    if( self->y+vy < targ->y || self->y+vy > targ->y+targ->h ) return 0;
	return 1;
}
int PlayerOverhead(Entity *self, Entity *targ, int vy){
	int cy;
	cy = 4;
	return 1;
}

int BoxCollide(Entity *self, Entity *targ){
    if( self->x+self->w < targ->x || self->x > targ->x+targ->w ) return 0;
    if( self->y+self->h < targ->y || self->y > targ->y+targ->h ) return 0;
	return 1;
}