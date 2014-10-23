#ifndef	_ENTITY_
#define _ENTITY_
/******
*
*	entity.h
*	contains all of the entity data of the game, including controllers, 
*	platform blocks, moveable characters, and other necessary items
*
******/

#include "SDL.h"
#include "SDL_keyboard.h"
#include "SDL_keysym.h"
#include "graphics.h"

#define MAXENTITIES 150

enum MODES{
	M_RED, M_BLUE, M_PURP
};

typedef struct Ent_s{
	Sprite			*sprite;
	int				x,y; /*Not using SDL_Rect since I don't need it*/
	int				w,h;
	int				vx,vy;
	int				mode; /*determines what form the world is in*/
	int				active;
	int				used;
	int				frame;
	int				solid;
	int				air;
	void			(*think)(struct Ent_s *self);
}Entity;

void	InitEnt();
Entity	*NewEnt();
void	DestEnt(Entity *ent);
void	ClearAllEnt();
void	DrawEnt(Entity *ent);
void	DrawEnts();
void	UpdateEnt();

/*Character stuff*/
Entity	*CreateChar(int x, int y, Sprite *sprite, int mode);
void	CharThink(Entity *self);

/*Blocks*/
Entity	*CreateBlock(int x, int y, Sprite *sprite, int mode);
void	BlockThink(Entity *self);

/*Obstacles*/
Entity	*CreateOb(int x, int y, Sprite *sprite, int mode);
void	ObThink(Entity *self);

/*Level Ender*/
Entity	*CreateGoal(int x, int y);
void	GoalThink(Entity *self);
#endif