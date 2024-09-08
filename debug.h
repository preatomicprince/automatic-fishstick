#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "settings.h"
#include "colider.h"
#include "level.h"
#include "input.h"
#include "entity.h"

typedef struct debug_tool_s{
    ent* selected_ent;
    int selected_vertex; //index of vertex in entity
    int adjusting_y;
}debug_tool_t;

void select_ent(debug_tool_t* debug_tool, ent* ent);

void set_selected_vertex(debug_tool_t* debug_tool, int vertex);

void update_debug_tool(debug_tool_t* debug_tool, level_t* level, input_t* input);

void draw_debug (SDL_Renderer* renderer, debug_tool_t* debug_tool);