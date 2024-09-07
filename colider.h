#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"
#include "sprite.h"

typedef struct colider_ {
    ivec2 vertex[16];
    int vertex_count;
    unsigned int active : 1;
    unsigned int is_convex : 1;
} colider;

colider* make_colider(spritesheet* spritesheet);

int adjust_colider(SDL_Renderer* renderer, spritesheet* spritesheet, colider* colider);

int draw_colider(SDL_Renderer* renderer, colider* colider, ivec2 pos);