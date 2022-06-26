#ifndef MAP_H
#define MAP_H

//ERROR = -3

//for tab_2d in map
typedef struct {

	//array 2D
	int* tab_2d;
	int width, height, size_tab_2d;
	int nb_objective;
	int nb_complete_objective;

}Grid;

typedef struct{
	SDL_Texture* wall_texture;
	SDL_Texture* box_texture;
	SDL_Texture* objective_texture;
	SDL_Texture* complete_texture;
	SDL_Rect pos_texture;
}Map_texture;

//Constructor and destructor
//grid
Grid* grid_tab_2d_init(int _width, int _height);
void grid_tab_2d_destroy(Grid* grid);	
//texture
Map_texture* map_texture_init(SDL_Renderer* renderer);
void map_texture_destroy(Map_texture* map_texure);


//debug
void grid_debug(Grid* grid);
void map_texture_debug(SDL_Renderer* renderer, Map_texture* map_texure);

//converted
int tab_converted_x_y_to_index(int x, int y, int size_x);

//manage value
void grid_set_value(Grid* grid, int index, int value);
void grid_set_value_x_y(Grid* grid, int index_x, int index_y, int value);
int grid_get_value(Grid* grid, int index);
int grid_get_value_x_y(Grid* grid, int index_x, int index_y);
//return index of value
int search_value(Grid* grid, int value);
void search_value_x_y(Grid* grid, int* index_x, int* index_y, int value);

//manage file level
void read_level(Grid* grid, const char* name_level);

//display
void display_map(SDL_Renderer* renderer, Grid* grid, Map_texture* map_texture);

#endif
