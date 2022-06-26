#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "constante.h"
#include "tools_sdl.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "play.h"

int main(void)
{
	//Variable
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	input_keys in;

	//init SDL
	SDL_Init(SDL_INIT_VIDEO);
	//init input key
	input_key_init(&in);

	//init window and renderer
	if(SDL_CreateWindowAndRenderer(SIZE_WINDOW_W, SIZE_WINDOW_H,0, &window, &renderer) != 0)
		fprintf(stderr, "Impossible de creer la fenetre et le rendu\n");
	
	//init map
	Grid* grid = grid_tab_2d_init(SIZE_MAP_W, SIZE_MAP_H);
	Map_texture* map_texture = map_texture_init(renderer);
	read_level(grid, "../level/level_test.txt");

	//init player
	Player* player = player_init(renderer, grid);
	
	while(in.window_is_open)
	{
		//check is wone
		if(is_wone(grid) == 1)
		{
			fprintf(stderr, "##### YOU WIN #####\n");
			SDL_Delay(1000);
			SDL_Quit();
			return EXIT_SUCCESS;
		}

		//input
		update_event(renderer, &in, player, grid);
		
		// display map
		display_map(renderer, grid, map_texture);
	
		// display player
		player_display(renderer, player);


		SDL_RenderPresent(renderer);
	}

	//destroy player
	player_destroy(player);

	//destroy map
	map_texture_destroy(map_texture);
	grid_tab_2d_destroy(grid);

	//destroy sdl
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return EXIT_SUCCESS;
}
