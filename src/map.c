#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "toolSDL.h"
#include "tools.h"
#include "player.h"
#include "map.h"

map map_init(SDL_Renderer* renderer)
{
	map m = tools_malloc(sizeof(struct _map));
	int i, j;
	
	m->block = tools_malloc(sizeof(int*) * NB_BLOCK_W);
	for(i = 0; i < NB_BLOCK_W; i++)
		m->block[i] = tools_malloc(sizeof(int) * NB_BLOCK_H);	

	for(i = 0; i < NB_BLOCK_W; i++)
	{
		for(j = 0; j < NB_BLOCK_H; j++)
			m->block[i][j] = 0; 
	}

	m->wall_block = map_create_texture(renderer, "img/mur.jpg");
	m->objective_block = map_create_texture(renderer, "img/objectif.png");	

	map_init_rect(m->wall_position);
	map_init_rect(m->objective_position);	

	if(SDL_QueryTexture(m->wall_block,NULL,NULL, &m->wall_position.w, &m->wall_position.h) != 0)
	{
		fprintf(stderr, "Impossible de charger la texture\n");
	}
	if(SDL_QueryTexture(m->objective_block,NULL,NULL, &m->objective_position.w, &m->objective_position.h) != 0)
	{
		fprintf(stderr, "Impossible de charger la texture\n");
	}

	int size = str_len("level1.txt");
	m->name_map = tools_malloc(sizeof(char) * size);
	str_copy(m->name_map,"level1.txt"); 
		

	m->nb_block = NB_BLOCK_W * NB_BLOCK_H; 

	return m;
}

void map_destroy(map m)
{
	int i;

	SDL_DestroyTexture(m->wall_block);
	SDL_DestroyTexture(m->objective_block);

	for(i = 0; i < NB_BLOCK_W; i++)
		tools_free(m->block[i], (sizeof(int) * NB_BLOCK_H));
	tools_free(m->block, (sizeof(int*) * NB_BLOCK_W));

	int size = str_len("level1.txt");
	tools_free(m->name_map, sizeof(char) * size);

	tools_free(m, sizeof(struct _map));
}

void map_create(SDL_Renderer* renderer, map m)
{
	map_read_level(m);
	map_set_block(renderer, m);

}


void debug(map m)
{
	int y, x;

	for(y = 0; y < NB_BLOCK_W; y++)
	{
		for(x = 0; x < NB_BLOCK_H; x++)
			fprintf(stderr, "%d", m->block[y][x]);

		fprintf(stderr, "\n");
	}
}


void map_read_level(map m)
{
	int c;
	int x = 0, y = 0;
	FILE *level = fopen(m->name_map, "r");
	if(level == NULL)
		fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", m->name_map);


	for(y = 0; y < NB_BLOCK_W; y ++)
	{
		for(x = 0; x < NB_BLOCK_H; x ++)
		{
			c = fgetc(level);
			if(c != 10)
			{
			int value = char_to_int(c);
			m->block[y][x] = value;
			}	
		}
		c = fgetc(level);
	}

 	


	if(fclose(level) == EOF)
		fprintf(stderr, "Impossible de fermer le fichier %s\n", m->name_map);

}

void map_set_block(SDL_Renderer* renderer, map m)
{
	int x, y;
	
	for(y = 0; y < NB_BLOCK_W; y ++)
	{
		for(x = 0; x < NB_BLOCK_H; x ++)
		{	
			m->wall_position.x = x * SIZE_BLOCK_H;
			m->wall_position.y = y * SIZE_BLOCK_W;
			m->objective_position.x = x * SIZE_BLOCK_H;
			m->objective_position.y = y * SIZE_BLOCK_W;


			switch(m->block[y][x])
			{
				case 1:
					SDL_RenderCopy(renderer, m->wall_block, NULL, &m->wall_position);
					break;
				case 2:
					SDL_RenderCopy(renderer, m->objective_block, NULL, &m->objective_position);
					break;

			}	
		}	
	}

}



void block_display(SDL_Renderer* renderer, map m)
{
	SDL_RenderCopy(renderer, m->wall_block, NULL, &m->wall_position);
}


SDL_Texture* map_create_texture(SDL_Renderer* renderer, char* name_img)
{
	SDL_Surface* img = IMG_Load(name_img);
	if(img == NULL)
		fprintf(stderr,"Impossible de charger l'image %s\n", name_img);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
	SDL_FreeSurface(img);
	if(texture == NULL)
		fprintf(stderr, "Impossible de creer la texture\n");

	return texture;
}

SDL_Rect map_init_rect(SDL_Rect rect)
{
	rect.x = 0;
	rect.y = 0;
	rect.w = 34;
	rect.h = 34;

	return rect;
}



