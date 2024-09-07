#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "settings.h"

typedef struct input_s {
    int key_left;
    int key_right;
    int key_up;
    int key_down;

    int mouse_l_click;
    int mouse_r_click;
    SDL_Point mouse_pos;
}input_t;

void handle_input(SDL_Event event, input_t* input);