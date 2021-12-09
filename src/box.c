#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "toolSDL.h"
#include "tools.h"
#include "player.h"
#include "map.h"
#include "box.h"

box box_create(SDL_Renderer* renderer)
{
	box b = tools_malloc(sizeof(struct _box));

	b->box_texture = box_create_texture(renderer, "img/caisse.jpg");
	b->box_valid_texture = box_create_texture(renderer, "img/caisse_ok.jpg");
	
	b->position = box_init_rect(b->position);
	
	return b;
}


void box_destroy(box b)
{
	SDL_DestroyTexture(b->box_texture);
	SDL_DestroyTexture(b->box_valid_texture);

	tools_free(b, sizeof(struct _box));
}

void box_display(SDL_Renderer* renderer, box b)
{
	SDL_RenderCopy(renderer, b->box_texture, NULL, &b->position);
}

SDL_Texture* box_create_texture(SDL_Renderer* renderer, char* name_img)
{
	SDL_Surface* img = IMG_Load(name_img);
	if(img == NULL)
		fprintf(stderr,"Impossible de charger l'image %s\n", name_img);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
	SDL_FreeSurface(img);
	if(texture == NULL)
		fprintf(stderr, "Impossible de creer la texture\n");

	return texture;
}

SDL_Rect box_init_rect(SDL_Rect rect)
{
	rect.w = 34;
	rect.h = 34;

	return rect;
}


