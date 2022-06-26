#ifndef CONSTANTE_H
#define CONSTANTE_H

//Window
#define SIZE_WINDOW_W SIZE_MAP_W * SIZE_BLOCK_W
#define SIZE_WINDOW_H SIZE_MAP_H * SIZE_BLOCK_H

//Texture
#define WALL "../texture/Wall.png"
#define BOX "../texture/Box.png"
#define OBJECTIVE "../texture/Objective.png"
#define COMPLETE_OBJECTIVE "../texture/Box_complete.png"
#define PLAYER_UP "../texture/Player_up.png"
#define PLAYER_DOWN "../texture/Player_down.png"
#define PLAYER_LEFT "../texture/Player_left.png"
#define PLAYER_RIGHT "../texture/Player_right.png"

//Size
#define SIZE_MAP_W 12
#define SIZE_MAP_H 12
#define SIZE_BLOCK_W 32
#define SIZE_BLOCK_H 32
#define SIZE_PLAYER_W 32
#define SIZE_PLAYER_H 32

//Block value
enum{EMPTY_BLOCK = 0, WALL_BLOCK = 1, BOX_BLOCK = 2, OBJECTIVE_BLOCK = 3, SPAWN_PLAYER = 4, COMPLETE_BLOCK = 5};

//Towards
enum{UP, DOWN, LEFT, RIGHT, UNMOVING};

#endif
