#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "input.h"
#include "constante.h"
#include "tools_sdl.h"
#include "player.h"


//Gestion input
void input_key_init(input_keys* in)
{
	for(int i = 0; i <= SDL_NUM_SCANCODES; i++)
		in->key[i] = SDL_FALSE;
	in->window_is_open = SDL_TRUE;	
}


void update_event(SDL_Renderer* renderer, input_keys* in, Player* player, Grid* grid)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				in->window_is_open = SDL_FALSE;
				break;
			
			case SDL_KEYDOWN:
				in->key[event.key.keysym.scancode] = SDL_TRUE;
				break;
			case SDL_KEYUP:
				in->key[event.key.keysym.scancode] = SDL_FALSE;
				break;

		}

	}
	//quit
	if(in->key[SDL_SCANCODE_ESCAPE])
		in->window_is_open = SDL_FALSE;
	//move player
	else if(in->key[SDL_SCANCODE_UP])
		player_move(renderer, player, grid, UP);	
	else if(in->key[SDL_SCANCODE_DOWN])
		player_move(renderer, player, grid, DOWN);	
	else if(in->key[SDL_SCANCODE_LEFT])
		player_move(renderer, player, grid, LEFT);	
	else if(in->key[SDL_SCANCODE_RIGHT])
		player_move(renderer, player, grid, RIGHT);
	else
		player_move(renderer, player, grid, UNMOVING);	

	SDL_Delay(100);
}

