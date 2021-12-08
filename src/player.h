#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "map.h"

#define SIZE_PLAYER_W 34
#define SIZE_PLAYER_H 34


enum{UP, DOWN, LEFT, RIGHT,NEUTRAL};

typedef struct _player* player;
struct _player{
	SDL_Texture** texture;
	SDL_Rect position;
	int speed;
	int rotation;
};

player player_create(SDL_Renderer* renderer, int start_position_x, int start_position_y);
void player_destroy(player j);

void player_display(SDL_Renderer* renderer, player j);
void player_move(player j, int direction, map m);
void player_create_texture(SDL_Renderer* renderer, player j);



#endif
