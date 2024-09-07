#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"
#include "sprite.h"
#include "colider.h"
#include "entity.h"

ent* init_ent(SDL_Rect rect, SDL_Renderer* renderer, const char* filepath){
    ent* new_ent = calloc(1, sizeof(ent));
    new_ent->vel = (ivec2){0,0};
    new_ent->rect = rect;
    new_ent->spritesheet_count = 0;
    if (filepath != NULL){
        new_ent->spritesheet = make_sprite(renderer, filepath, 0);
        new_ent->spritesheet_count += 1;
    }
    return new_ent;
}

int add_colider(ent* ent){
    ent->colider = make_colider(ent->spritesheet);
    return 1;
}

int render_ent(SDL_Renderer* renderer, ent* ent){
    render(renderer, ent->spritesheet, (ivec2){ent->rect.x, ent->rect.y});
    return 1;
}

int draw_ent_outline(SDL_Renderer* renderer, ent* ent){
    SDL_SetRenderDrawColor(renderer, 0, 0, 254, 0);
    SDL_RenderDrawRect(renderer, &ent->rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    return 1;
}
