#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"
#include "sprite.h"
#include "colider.h"

typedef struct ent_{
    SDL_Rect rect;
    ivec2 vel;
    spritesheet* spritesheet;
    int spritesheet_count;
    colider* colider;
}ent;

ent* init_ent(SDL_Rect rect, SDL_Renderer* renderer, const char* filepath);

int add_colider(ent* ent);

int render_ent(SDL_Renderer* renderer, ent* ent);

int draw_ent_outline(SDL_Renderer* renderer, ent* ent);
