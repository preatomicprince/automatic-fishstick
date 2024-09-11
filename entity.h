#ifndef ENTITY
#define ENTITY

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"
#include "sprite.h"
#include "colider.h"

typedef struct ent_{
    SDL_Rect rect;
    SDL_Point vel;
    spritesheet* spritesheet;
    int spritesheet_count;
    colider* colider;
}ent;

ent* init_ent(SDL_Rect rect, SDL_Renderer* renderer, spritesheet* spritesheet, const char* filepath);

void add_colider(ent* ent);

int check_collision(ent e1, ent e2);

int render_ent(SDL_Renderer* renderer, ent* ent);

int draw_ent_outline(SDL_Renderer* renderer, ent* ent);

void y_sort_ents(ent** ents, int ent_count);

#endif