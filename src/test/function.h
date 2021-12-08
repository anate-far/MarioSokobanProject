#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "tools.h"

typedef struct _player* player;
struct _player{

	SDL_Texture* texture; 
	SDL_Rect position;
};

typedef struct _block* block;
struct _block{
	SDL_Texture* wall_block; 

};

player player_create(SDL_Renderer* renderer);
void player_destroy(player j);

SDL_Texture* player_create_texture(SDL_Renderer* renderer);
//void player_display(SDL_Renderer* renderer, SDL_Texture* txture);
void player_display(SDL_Renderer* renderer, player j);

int read_block_value(int nb_caracter);
void set_block();
void create_block(SDL_Renderer* renderer);


#endif
