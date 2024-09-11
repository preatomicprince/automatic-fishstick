#ifndef COLIDER
#define COLIDER

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"
#include "sprite.h"

typedef struct colider_ {
    SDL_Point vertex[16];
    int vertex_count;
    int y_offset;
    unsigned int active : 1;
    unsigned int is_convex : 1;
} colider;

colider* make_colider(spritesheet* spritesheet);

int adjust_colider(SDL_Renderer* renderer, spritesheet* spritesheet, colider* colider);

int draw_colider(SDL_Renderer* renderer, colider* colider, SDL_Point pos);

int ccw(SDL_Point p1, SDL_Point p2, SDL_Point p3);

int check_intersection(SDL_Point p1, SDL_Point p2, SDL_Point p3, SDL_Point p4);

#endif

