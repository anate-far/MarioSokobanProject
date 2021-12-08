#include<SDL.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "toolSDL.h"


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
