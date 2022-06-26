#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "constante.h"
#include "tools_sdl.h"
#include "player.h"
#include "map.h"


//constructor and destructor
Player* player_init(SDL_Renderer* renderer, Grid* grid)
{
	Player* player = malloc(sizeof(Player));

	//Init texture
	player->up_texture = create_texture(renderer, PLAYER_UP);
	player->down_texture = create_texture(renderer, PLAYER_DOWN);
	player->left_texture = create_texture(renderer, PLAYER_LEFT);
	player->right_texture = create_texture(renderer, PLAYER_RIGHT);
	player->display_texture = player->down_texture; 
	

	//init pos	
	player->pos_player.w = SIZE_PLAYER_W;
	player->pos_player.h = SIZE_PLAYER_H;	
	//set stater pos
	search_value_x_y(grid, &player->pos_player.x, &player->pos_player.y, SPAWN_PLAYER);
	player->pos_player.x *= SIZE_PLAYER_W;
	player->pos_player.y *= SIZE_BLOCK_H;
	
	//Set pos texture
	SDL_QueryTexture(player->up_texture, NULL, NULL, &player->pos_player.w, &player->pos_player.h);
	SDL_QueryTexture(player->down_texture, NULL, NULL, &player->pos_player.w, &player->pos_player.h);
	SDL_QueryTexture(player->left_texture, NULL, NULL, &player->pos_player.w, &player->pos_player.h);
	SDL_QueryTexture(player->right_texture, NULL, NULL, &player->pos_player.w, &player->pos_player.h);

	//init speed player
	player->speed = SIZE_BLOCK_W;

	return player;
}

void player_destroy(Player* player)
{
	if(player == NULL)
		return;

	//destroy texture
	SDL_DestroyTexture(player->up_texture);
	SDL_DestroyTexture(player->down_texture);
	SDL_DestroyTexture(player->left_texture);
	SDL_DestroyTexture(player->right_texture);

	//destroy struct player
	free(player);
}

//display
void player_display(SDL_Renderer* renderer, Player* player)
{
	SDL_RenderCopy(renderer, player->display_texture, NULL, &player->pos_player);
}

//player collision object
void player_box_colision(Player* player, Grid* grid, int speed_x, int speed_y)
{
	int index_1;
	int index_2;

	//set index
	//for y -1
	index_1 = tab_converted_x_y_to_index(((player->pos_player.x + speed_x) / SIZE_BLOCK_W), ((player->pos_player.y - speed_y) / SIZE_BLOCK_W), grid->width);
	//for y -2
	index_2 = tab_converted_x_y_to_index(((player->pos_player.x + (speed_x * 2)) / SIZE_BLOCK_W), ((player->pos_player.y  - (speed_y * 2 )) / SIZE_BLOCK_W), grid->width);
	
	//check if one box
	if((grid->tab_2d[index_1] == BOX_BLOCK) || (grid->tab_2d[index_1] == COMPLETE_BLOCK))
	{	
		//check if Tow box or wall 
		if((grid->tab_2d[index_2] == BOX_BLOCK) || (grid->tab_2d[index_2] == WALL_BLOCK) || (grid->tab_2d[index_2] == COMPLETE_BLOCK ))
		{
			//stop player
			player->pos_player.y += speed_y;
			player->pos_player.x -= speed_x;	
		}
		//chekc if objective
		else if(grid->tab_2d[index_2] == OBJECTIVE_BLOCK)
		{
		
			grid->tab_2d[index_1] = EMPTY_BLOCK;	
			grid->tab_2d[index_2] = COMPLETE_BLOCK;
		}
		//if there is juste one box
		else
		{
			//check if objective or not
			if(grid->tab_2d[index_1] == COMPLETE_BLOCK)
				grid->tab_2d[index_1] = OBJECTIVE_BLOCK;
			else
				grid->tab_2d[index_1] = EMPTY_BLOCK;
			
			grid->tab_2d[index_2] = BOX_BLOCK;	
		}
	}

}

//movement
void player_move(SDL_Renderer* renderer, Player* player, Grid* grid, int towards)
{
	//Error
	if(player == NULL)
		return;

	//Movement
	switch(towards )
	{	
		case UP:	
			//check wall collision
			if(grid->tab_2d[tab_converted_x_y_to_index((player->pos_player.x / SIZE_BLOCK_W), ((player->pos_player.y - player->speed) / SIZE_BLOCK_W), grid->width)] != WALL_BLOCK)
			{
				//move player
				player_box_colision(player, grid, 0, player->speed);
				player->pos_player.y -= player->speed;
						
			}
			//apply texture
			player->display_texture = player->up_texture;
			break;
		case DOWN:
			//check wall collision
			if(grid->tab_2d[tab_converted_x_y_to_index((player->pos_player.x / SIZE_BLOCK_W), ((player->pos_player.y + player->speed) / SIZE_BLOCK_W), grid->width)] != WALL_BLOCK)
			{
				//move player
				player_box_colision(player, grid, 0, -player->speed);
				player->pos_player.y += player->speed;
					
			}
			//apply texture
			player->display_texture = player->down_texture;
			break;
		case LEFT:
			//chekc wall collision
			if(grid->tab_2d[tab_converted_x_y_to_index(((player->pos_player.x - player->speed )/ SIZE_BLOCK_W), (player->pos_player.y / SIZE_BLOCK_W), grid->width)] != WALL_BLOCK)
			{
				//move player
				player_box_colision(player, grid, -player->speed, 0);
				player->pos_player.x -= player->speed;
				
			}
			//apply texture
			player->display_texture = player->left_texture;	
			break;
		case RIGHT:
			//chekc wall collision
			if(grid->tab_2d[tab_converted_x_y_to_index(((player->pos_player.x + player->speed )/ SIZE_BLOCK_W), (player->pos_player.y / SIZE_BLOCK_W), grid->width)] != WALL_BLOCK)
			{
				//move player
				player_box_colision(player, grid, player->speed, 0);	
				player->pos_player.x += player->speed;
				
			}
			//apply texture
			player->display_texture = player->right_texture;	
			break;
		default:
			//apply texture
			player->display_texture = player->down_texture;	
			break;



	}

	SDL_RenderClear(renderer);
}
