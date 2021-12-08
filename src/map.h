#ifndef MAP_H
#define MAP_H

#define SIZE_BLOCK_W 34
#define SIZE_BLOCK_H 34
#define NB_BLOCK_W 12//y
#define NB_BLOCK_H 12//x

enum{VOID_BLOCK, WALL_BLOCK, BOX, CHECK, PLAYER};

typedef struct _map* map;
struct _map{
	int** block;
	SDL_Texture* wall_block;
	SDL_Texture* objective_block; 
	SDL_Rect wall_position; 
	SDL_Rect objective_position;
	char* name_map;
	int nb_block; 
};
struct _box{

};

map map_init(SDL_Renderer* renderer);
void map_destroy(map m);
void map_create(SDL_Renderer* renderer, map m);
void debug(map m);
void map_set_block_init(map m);
void map_read_level(map m);
void map_set_block(SDL_Renderer* renderer, map m);
void block_display(SDL_Renderer* renderer, map m);
SDL_Texture* map_create_texture(SDL_Renderer* renderer, char* name_img);
SDL_Rect map_init_rect(SDL_Rect rect);



#endif
