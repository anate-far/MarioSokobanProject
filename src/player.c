#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "toolSDL.h"
#include "tools.h"
#include "player.h"
#include "map.h"
#include "box.h"

player player_create(SDL_Renderer* renderer, int start_position_x, int start_position_y)
{
	player j = tools_malloc(sizeof(struct _player));
	j->texture = tools_malloc(sizeof(SDL_Texture*) * 4);
	
	j->position.x = start_position_x;
	j->position.y = start_position_y;
	j->position.w = SIZE_PLAYER_W;
	j->position.h = SIZE_PLAYER_H;

	j->speed = SIZE_BLOCK_W;	

	player_create_texture(renderer, j);

	return j; 
}


void player_destroy(player j)
{
	int i = 0;
	for(i = 0; i < 4; i++)
		SDL_DestroyTexture(j->texture[i]);
	tools_free(j->texture, sizeof(SDL_Texture*) * 4);
	tools_free(j, sizeof(struct _player));
}



void player_display(SDL_Renderer* renderer, player j)
{
	SDL_RenderCopy(renderer, j->texture[j->rotation], NULL, &j->position);
       
}


void player_move(player j, int direction, map m)
{
	if(direction == DOWN)
	{	
		j->rotation = 0;
		SDL_QueryTexture(j->texture[0], NULL, NULL, &j->position.w, &j->position.h);
	
		if(m->block[(j->position.y + j->speed) / 34][j->position.x / 34] == 1)
			j->position.y += 0;
		else if(check_box_colision(j, m) != 0)
			printf("1");
		else
			
			j->position.y += j->speed;
		

	}	
	
	if(direction == UP)
	{
		j->rotation = 1;
		SDL_QueryTexture(j->texture[1], NULL, NULL, &j->position.w, &j->position.h);
		
		if(m->block[(j->position.y - j->speed) / 34][j->position.x / 34] == 1)
			j->position.y += 0;	
		else		
			j->position.y -= j->speed;	
	}
	if(direction == RIGHT)
	{
		j->rotation = 2;
		SDL_QueryTexture(j->texture[2], NULL, NULL, &j->position.w, &j->position.h);
		
		if(m->block[j->position.y / 34][(j->position.x + j->speed) / 34] == 1)
			j->position.x += 0;	
		else		
			j->position.x += j->speed;
	}
	if(direction == LEFT)
	{
		j->rotation = 3;
		SDL_QueryTexture(j->texture[3], NULL, NULL, &j->position.w, &j->position.h);
		
		if(m->block[j->position.y / 34][(j->position.x - j->speed) / 34] == 1)
			j->position.x += 0;	
		else		
			j->position.x -= j->speed;
;
	}

}


void player_create_texture(SDL_Renderer* renderer, player j)
{
	
	SDL_Surface* mario_bas = IMG_Load("img/mario_bas.gif");
	if(mario_bas== NULL)
		fprintf(stderr, "Impossible de charger l'image img/mario_bas\n");
	SDL_Surface* mario_haut = IMG_Load("img/mario_haut.gif");
	if(mario_haut== NULL)
		fprintf(stderr, "Impossible de charger l'image img/mario_haut\n");
	SDL_Surface* mario_droite = IMG_Load("img/mario_droite.gif");
	if(mario_droite== NULL)
		fprintf(stderr, "Impossible de charger l'image img/mario_droite\n");
	SDL_Surface* mario_gauche = IMG_Load("img/mario_gauche.gif");
	if(mario_gauche== NULL)
		fprintf(stderr, "Impossible de charger l'image img/mario_gauche\n");

	j->texture[0] = SDL_CreateTextureFromSurface(renderer, mario_bas);
	if(j->texture[0] == NULL)
		fprintf(stderr, "Impossible de charger la texture\n");
	j->texture[1] = SDL_CreateTextureFromSurface(renderer, mario_haut);
	if(j->texture[1] == NULL)
		fprintf(stderr, "Impossible de charger la texture\n");
	j->texture[2] = SDL_CreateTextureFromSurface(renderer, mario_droite);
	if(j->texture[2] == NULL)
		fprintf(stderr, "Impossible de charger la texture\n");
	j->texture[3] = SDL_CreateTextureFromSurface(renderer, mario_gauche);
	if(j->texture[3] == NULL)
		fprintf(stderr, "Impossible de charger la texture\n");

	SDL_FreeSurface(mario_bas);
	SDL_FreeSurface(mario_haut);			
	SDL_FreeSurface(mario_droite);
	SDL_FreeSurface(mario_gauche);

}


int check_box_colision(player j,map m)
{
	int i,v;
	for (i = 0; i < m->nb_box; i ++)
	{
		for(v = 0; v < m->nb_box; v ++)
		{
			if(m->block[(m->tab_box[i]->position.y + j->speed) / 34][m->tab_box[i]->position.x / 34] == 1)
			{
				m->tab_box[i]->position.y += 0;
			}	

			else if((j->position.y + j->speed) == m->tab_box[i]->position.y && j->position.x == m->tab_box[i]->position.x)
			{
				m->tab_box[i]->position.y += j->speed;	
			}
		
		}
	}	

	return 3;
}
