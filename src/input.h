#ifndef INPUT_H
#define INPUT_H

#include "map.h"
#include "player.h"

typedef struct{
	SDL_bool key[SDL_NUM_SCANCODES];
	SDL_bool window_is_open;	
}input_keys;

void input_key_init(input_keys* in);
void update_event(SDL_Renderer* renderer, input_keys* in, Player* player, Grid* grid);

#endif 
