#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "function.h"
#include "tools.h"


SDL_Texture* player_create_texture(SDL_Renderer* renderer)
{
	SDL_Surface* img = IMG_Load("../img/mario_bas.gif");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
       	SDL_FreeSurface(img);

	return texture;	

}

/*void player_display(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_Rect* position = tools_malloc(sizeof(SDL_Rect));

	position->x = 10;
	position->y = 20;
	position->w = 34;
	position->h = 34;
	
	SDL_QueryTexture(texture,NULL, NULL, &position->w, &position->h); 

	SDL_RenderCopy(renderer, texture, NULL, position); 
}*/


player player_create(SDL_Renderer* renderer)
{
	player j = tools_malloc(sizeof(struct _player));
	
	SDL_Surface* img = IMG_Load("../img/mario_bas.gif");
	j->texture = SDL_CreateTextureFromSurface(renderer, img);
       	SDL_FreeSurface(img);

	j->position.x = 10;
	j->position.y = 20;
	j->position.w = 34;
	j->position.h = 34; 
		
	SDL_QueryTexture(j->texture, NULL, NULL, &j->position.w, &j->position.h);

	return j; 
}

void player_destroy(player j)
{
	SDL_DestroyTexture(j->texture);
	tools_free(j, sizeof(struct _player));
}

void player_display(SDL_Renderer* renderer, player j)
{

	SDL_RenderCopy(renderer, j->texture, NULL, &j->position); 
}


int read_block_value(int nb_caracter)
{
	int result = 0; 
	int i;
	char value;

	FILE* niveau = fopen("testMap.txt", "r");
	if(niveau == NULL)
		fprintf(stderr,"Impossible d ouvrir le fichier\n");

	for(i = 0; i <= nb_caracter; i++)
		value = fgetc(niveau);
	result = char_to_int(value);


	if(fclose(niveau) == EOF)
		fprintf(stderr, "Impossible de fermer le fichier\n");


	return result; 
}



