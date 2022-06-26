#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "map.h"
#include "constante.h"
#include "tools_sdl.h"


//Constructor and destructor
//grid
Grid* grid_tab_2d_init(int _width, int _height)
{
	Grid* grid = malloc(sizeof(Grid));

	//init size value
	grid->width = _width;
	grid->height = _height;
	grid->size_tab_2d = _width * _height;

	//init tab_2d_array
	grid->tab_2d = malloc(sizeof(int) * grid->size_tab_2d);
	//init value
	for(int i = 0; i < grid->size_tab_2d; i++)
		grid->tab_2d[i] = 0;

	//init objectiv
	grid->nb_objective = 0;
	grid->nb_complete_objective = 0;

	return grid;
}

void grid_tab_2d_destroy(Grid* grid)
{
	if(grid == NULL)
		return;
	
	//destroy tab_2d_array
	free(grid->tab_2d);

	//destroy grid
	free(grid);
}
//texture
Map_texture* map_texture_init(SDL_Renderer* renderer)
{
	Map_texture* map_texture = malloc(sizeof(Map_texture));

	//init texture
	map_texture->wall_texture = create_texture(renderer, WALL);
	map_texture->box_texture = create_texture(renderer, BOX);
	map_texture->objective_texture = create_texture(renderer, OBJECTIVE);
	map_texture->complete_texture = create_texture(renderer, COMPLETE_OBJECTIVE);

	//init pos
	map_texture->pos_texture.x = 0;
	map_texture->pos_texture.y = 0;
	map_texture->pos_texture.w = SIZE_BLOCK_W;	
	map_texture->pos_texture.h = SIZE_BLOCK_H;

	//Init value texture
	SDL_QueryTexture(map_texture->wall_texture, NULL, NULL, &map_texture->pos_texture.w, &map_texture->pos_texture.h);
	SDL_QueryTexture(map_texture->box_texture, NULL, NULL, &map_texture->pos_texture.w, &map_texture->pos_texture.h);
	SDL_QueryTexture(map_texture->objective_texture, NULL, NULL, &map_texture->pos_texture.w, &map_texture->pos_texture.h);
	SDL_QueryTexture(map_texture->complete_texture, NULL, NULL, &map_texture->pos_texture.w, &map_texture->pos_texture.h);

	return map_texture;
}

void map_texture_destroy(Map_texture* map_texture)
{
	if(map_texture == NULL)
		return;

	//destroy texture
	SDL_DestroyTexture(map_texture->wall_texture);
	SDL_DestroyTexture(map_texture->box_texture);
	SDL_DestroyTexture(map_texture->objective_texture);

	//destroy struct map_texture
	free(map_texture);
}

//debug
void grid_debug(Grid* grid)
{
	int x = 0;
	for(int i = 0; i < grid->size_tab_2d; i++)
	{
		//loop for display array
		if(x == grid->width)
		{
			//check id end line
			fprintf(stderr, "\n");
			x = 0;
		}

		//right value
		fprintf(stderr, "%d", grid->tab_2d[i]);
		x++;

	}
	fprintf(stderr, "\n\n");
}


void map_texture_debug(SDL_Renderer* renderer, Map_texture* map_texure)
{
	SDL_RenderCopy(renderer, map_texure->wall_texture, NULL, &map_texure->pos_texture);
	map_texure->pos_texture.x += 32;
	SDL_RenderCopy(renderer, map_texure->box_texture, NULL, &map_texure->pos_texture);
	map_texure->pos_texture.x += 32;
	SDL_RenderCopy(renderer, map_texure->objective_texture, NULL, &map_texure->pos_texture);
	map_texure->pos_texture.x = 0;
}

//converted
int tab_converted_x_y_to_index(int x, int y, int size_x) 
{
	int index = 0;

	index = size_x * y + x;

	return index;
}

void grid_set_value(Grid* grid, int index, int value)
{
	//Error
	if(grid == NULL)
		return;
	if((index < 0) || ( index >= grid->size_tab_2d))
	{
		fprintf(stderr, "ERROR <grid_set_value> : index invalide\n");
	       return;	
	}

	grid->tab_2d[index] = value; 

}

void grid_set_value_x_y(Grid* grid, int index_x, int index_y, int value)
{
	//Error
	if(grid == NULL)
		return;
	if((index_x < 0) || (index_x >= grid->width) || (index_y < 0) || (index_y >= grid->height))
	{
		fprintf(stderr, "ERROR <grid_set_value_x_y> : index invalide\n");
		return;
	}

	grid_set_value(grid, tab_converted_x_y_to_index(index_x, index_y, grid->width), value);

}

int grid_get_value(Grid* grid, int index)
{
	//Error
	if(grid == NULL)
		return -3;
	if((index < 0) || ( index >= grid->size_tab_2d))
	{
		fprintf(stderr, "ERROR <grid_get_value> : index invalide\n");
	       return -3;	
	}

	return grid->tab_2d[index];

}
int grid_get_value_x_y(Grid* grid, int index_x, int index_y)
{
	//Error
	if(grid == NULL)
		return -3;
	if((index_x < 0) || (index_x >= grid->width) || (index_y < 0) || (index_y >= grid->height))
	{
		fprintf(stderr, "ERROR <grid_get_value_x_y> : index invalide\n");
		return -3;
	}

	return grid_get_value(grid, tab_converted_x_y_to_index(index_x, index_y, grid->width));
}

//return index of value
int search_value(Grid* grid, int value)
{
	for(int i = 0; i < grid->size_tab_2d; i++)
	{
		if(grid->tab_2d[i] == value)
			return i;
	}

	return -3;
}

void search_value_x_y(Grid* grid, int*	index_x, int* index_y, int value)
{
	*index_x = -3;
	*index_y = -3;

	for(int i = 0; i < grid->height; i++)
	{
		for(int j = 0; j < grid->width; j++)
		{
			if(grid->tab_2d[tab_converted_x_y_to_index(j, i, grid->width)] == value )
			{
				*index_x = j;
				*index_y = i;
			}
		}
	}

}


//manage file level
void read_level(Grid* grid, const char* name_level)
{
	//start number objective is 0
	grid->nb_objective = 0;

	//open file 
	FILE* level = fopen(name_level, "r");
	if(level == NULL)
	{
		fprintf(stderr, "ERROR <read_level> : Impossible de lire le fichier -> %s\n", name_level);
		return;
	}

	//loop for read file
	for(int i = 0;i < grid->size_tab_2d; i++)
	{
		int value = fgetc(level);
		if(value == '\n')
			value = fgetc(level);

		//count the number of objective
		if(char_to_int(value) == OBJECTIVE_BLOCK )
			grid->nb_objective ++;

		grid->tab_2d[i] = char_to_int(value); 
	}	

	fclose(level);

}

//display
void display_map(SDL_Renderer* renderer, Grid* grid, Map_texture* map_texture)
{
	for(int y = 0; y < grid->height; y++)
	{	

		for(int x = 0; x < grid->width; x++)
		{
			map_texture->pos_texture.x = x * SIZE_BLOCK_W;
			map_texture->pos_texture.y = y * SIZE_BLOCK_H;

			int value = tab_converted_x_y_to_index(x, y, grid->width);

			switch(grid->tab_2d[value])
			{
				case WALL_BLOCK:
					SDL_RenderCopy(renderer,map_texture->wall_texture, NULL, &map_texture->pos_texture);
					break;
				case BOX_BLOCK:
					SDL_RenderCopy(renderer,map_texture->box_texture, NULL, &map_texture->pos_texture);
					break;
				case OBJECTIVE_BLOCK:
					SDL_RenderCopy(renderer,map_texture->objective_texture, NULL, &map_texture->pos_texture);
					break;
				case COMPLETE_BLOCK:
					SDL_RenderCopy(renderer, map_texture->complete_texture, NULL, &map_texture->pos_texture);
				       break;	
			}

		}
		
		
	}
}
