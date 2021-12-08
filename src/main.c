#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "toolSDL.h"
#include "tools.h"
#include "player.h"
#include "map.h"

#define SIZE_WINDOW_W SIZE_BLOCK_W * NB_BLOCK_W
#define SIZE_WINDOW_H SIZE_BLOCK_H * NB_BLOCK_H

int main(int argc, char** argv)
{
	tools_memory_init();

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_bool window_is_open = SDL_TRUE;	
	char * name = "img/mario_bas.gif";	


	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		clearRessources("Impossible de charger la sdl", NULL,NULL, NULL); 

	if (SDL_CreateWindowAndRenderer( SIZE_WINDOW_H, SIZE_WINDOW_W, 0, &window, &renderer))
			clearRessources("Impossible de creer une fenetre et un rendu", NULL,NULL,NULL);	

	player mario = player_create(renderer, "img/mario_bas.gif", 170, 204);
	map level = map_init(renderer);


	while(window_is_open)
	{
	
		
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					window_is_open = SDL_FALSE; 
					

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							window_is_open = SDL_FALSE; 
							break;

						case SDLK_DOWN:
							player_move(mario, DOWN, level);
							break;
						case SDLK_UP:
							player_move(mario, UP, level);
							break;
						case SDLK_RIGHT:
							player_move(mario, RIGHT, level);
							break;
						case SDLK_LEFT:
							player_move(mario, LEFT, level);
							break;


						default:
							continue;		
					}
					break;
	

				default:
					player_move(mario, NEUTRAL, level);
					break; 
			}

			
		}

		//player_colision(mario, level);
		
		if(SDL_RenderClear(renderer) != 0)
		       clearRessources("Impossible de clear le rendu", window, renderer, NULL); 
				
	
		map_create(renderer, level);	
		player_display(renderer, mario),	

		SDL_RenderPresent(renderer); 
	}



	

		player_destroy(mario);
		map_destroy(level);

		clearRessources(NULL, window, renderer, NULL); 

		tools_check_at_end_of_app();
	 

	return EXIT_SUCCESS; 
}
