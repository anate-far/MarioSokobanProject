#include<SDL.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <SDL_image.h>
#include "tools_sdl.h"

//Gestion error
void clearRessources(const char *message, SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture)
{
	if(texture != NULL)
	{
		SDL_DestroyTexture(texture);
	}

	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	if( window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	if(message != NULL)
	{
		SDL_Log("Error : %s > %s\n", message, SDL_GetError());
	}
	SDL_Quit();
	exit(EXIT_FAILURE);

}


//Création texture
SDL_Texture* create_texture(SDL_Renderer* renderer, const char* name_img)
{
	SDL_Surface* img = IMG_Load(name_img);
	if(name_img == NULL)
		fprintf(stderr,"ERROR <set_texture> : Impossible de charger l image %s\n", name_img);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
	if(texture == NULL)
		fprintf(stderr,"Error <set_texture> : Impossible de charger la texture de l'image %s\n", name_img);

	SDL_FreeSurface(img);
	

	return texture;
}


int string_to_int(char* str)
{
	int result = 0, i;

	for(i = 0; str[i] != '\0'; i ++)
	{
		result *= 10; 
		result += str[i] - 48;


	}	

	return result; 
}

int char_to_int(char c)
{
	int result = 0;
	
	result = c -48;
	return result;
}
