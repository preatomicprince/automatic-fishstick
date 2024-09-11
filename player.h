#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "input.h"
#include "entity.h"
#include "sprite.h"

/*typedef enum direction_e{
    up,
    up_right, 
    right, 
    down_right, 
    down, 
    down_left, 
    left, 
    up_left
}direction_t;*/

typedef struct player_s{
    ent* ent;
    SDL_Point vel;
    fvec2_t pos;
    spritesheet* spritesheets[32];
}player_t;

player_t* init_player(SDL_Renderer* renderer);

void update_player(player_t* player, input_t* , level_t level);

void load_player_textures(SDL_Renderer* renderer, player_t* player);

int render_player(SDL_Renderer* renderer, player_t* player);
