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

//check if is wone
int is_wone(Grid* grid)
{
	grid->nb_complete_objective = 0;

	//see if there are complete block
	for(int i = 0; i < grid->size_tab_2d; i++)
	{
		if(grid->tab_2d[i] == COMPLETE_BLOCK)
			grid->nb_complete_objective ++;
	}

	//return true if is every objective complete
	if(grid->nb_objective == grid->nb_complete_objective)
	       return 1;
	else 
		return 0;	
}

