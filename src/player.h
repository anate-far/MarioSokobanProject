#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

typedef struct{
	SDL_Texture* up_texture;
	SDL_Texture* down_texture;
	SDL_Texture* left_texture;
	SDL_Texture* right_texture;
	SDL_Texture* display_texture;
	SDL_Rect pos_player;
	int speed;
}Player;

//constructor and destructor
Player* player_init(SDL_Renderer* renderer, Grid* grid);
void player_destroy(Player* player);

//display
void player_display(SDL_Renderer* renderer, Player* player);

//player collision object
void player_box_colision(Player* player, Grid* grid, int speed_x, int speed_y);

//movement
void player_move(SDL_Renderer* renderer, Player* player, Grid* grid, int towards);


#endif
