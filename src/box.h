#ifndef BOX_H
#define BOX_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "map.h"
#include "player.h"

typedef struct _box* box;
struct _box{
	SDL_Texture* box_texture;
	SDL_Texture* box_valid_texture;
	SDL_Rect position;
	int start_x;
	int start_y;

};

box box_create(SDL_Renderer* renderer);
void box_destroy(box b);

void box_display(SDL_Renderer* renderer, box b);

SDL_Texture* box_create_texture(SDL_Renderer* renderer, char* name_img);
SDL_Rect box_init_rect(SDL_Rect rect);



#endif
