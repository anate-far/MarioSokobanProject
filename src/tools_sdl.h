#ifndef TOOLBASE_H
#define TOOLBASE_H

#include<SDL.h>


//manage error
void clearRessources(const char *message, SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture);

//Créatioin texture
SDL_Texture* create_texture(SDL_Renderer* renderer, const char* name_img);

//manage char 
int string_to_int(char* str);
int char_to_int(char c);

#endif
