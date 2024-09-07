#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "settings.h"
#include "entity.h"
#include "level.h"
#include "debug.h"

void select_ent(debug_tool_t* debug_tool, ent* ent){
    debug_tool->selected_ent = ent;
}

void set_selected_vertex(debug_tool_t* debug_tool, int vertex){
    debug_tool->selected_vertex = vertex;
}

int select_vertex(input_t* input, ent* ent){
    for(int i = 0; i < ent->colider->vertex_count; i++){
        if (ent->colider->vertex[i].x - VERT_SIZE/2 + ent->rect.x < input->mouse_pos.x && input->mouse_pos.x < ent->colider->vertex[i].x + ent->rect.x + VERT_SIZE/2){
            if (ent->colider->vertex[i].y - VERT_SIZE/2 + ent->rect.y < input->mouse_pos.y && input->mouse_pos.y < ent->colider->vertex[i].y + ent->rect.y + VERT_SIZE/2){
                return i;
            }
        }
    }
    return -1;
}

void update_debug_tool(debug_tool_t* debug_tool, level_t* level, input_t* input){
    if (input->mouse_l_click){

        /*SELECT ENTITY*/
        if (debug_tool->selected_ent == NULL){
            for (int i = 0; i < level->ent_count; i++){
                if (
                    input->mouse_pos.x > level->ents[i]->rect.x 
                    && input->mouse_pos.x < level->ents[i]->rect.x + level->ents[i]->rect.w
                    && input->mouse_pos.y > level->ents[i]->rect.y 
                    && input->mouse_pos.y < level->ents[i]->rect.y + level->ents[i]->rect.h)
                {
                    debug_tool->selected_ent = level->ents[i];
                    break;
                }
                /*DESELECT ENTITY*/
                debug_tool->selected_ent = NULL;
            }

        /*SELECT VERTEX*/
        }else if (debug_tool->selected_vertex == -1){
            debug_tool->selected_vertex = select_vertex(input, debug_tool->selected_ent);

        /*DRAG VERTEX*/    
        }else { //if ent and vertex selected
            debug_tool->selected_ent->colider->vertex[debug_tool->selected_vertex].x = input->mouse_pos.x;
            debug_tool->selected_ent->colider->vertex[debug_tool->selected_vertex].y = input->mouse_pos.y;
        }
    }else {
        /*DESELECT VERTEX*/
        debug_tool->selected_vertex = -1;
    }
}