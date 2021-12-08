#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "tools.h"
#include "function.h"

int main(int argc, char** argv)
{
	tools_memory_init();

	SDL_Window* window; 
	SDL_Renderer* renderer; 
	SDL_bool window_is_open = SDL_TRUE; 

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

	//SDL_Texture* mario = player_create_texture(renderer);

	player mario = player_create(renderer);
	printf("value = %d\n", read_block_value(0));
	printf("value = %d\n", read_block_value(1));

	while(window_is_open)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					window_is_open = SDL_FALSE;
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							window_is_open = SDL_FALSE;
							break;

						default:
							continue;
					}break;

				
				default:
					break;
			}
		}

		

		SDL_RenderClear(renderer);
	
		player_display(renderer, mario);			

		SDL_RenderPresent(renderer);
	}


	player_destroy(mario);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window); 

	tools_check_at_end_of_app();
	
	return EXIT_SUCCESS;
}
