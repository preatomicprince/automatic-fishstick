#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"

SDL_Texture* make_texture(SDL_Renderer* renderer, const char* filepath);

typedef struct spritesheet_{
    SDL_Texture* texture;
    int frame_count;
    int current_frame;

    ivec2 size;
}spritesheet;

spritesheet* make_sprite(SDL_Renderer* renderer, const char* filepath, int framecount);

int render(SDL_Renderer* renderer, spritesheet* spritesheet, ivec2 pos);
