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

void select_y_offset(input_t* input, debug_tool_t* debug_tool, ent* ent){
    int y = ent->rect.y + ent->colider->y_offset;
    if (input->mouse_pos.y < y + VERT_SIZE && input->mouse_pos.y > y - VERT_SIZE){
        debug_tool->adjusting_y = 1;
    }
}

int mouse_ent_collision(input_t* input, ent* ent){
    if (
        input->mouse_pos.x > ent->rect.x && 
        input->mouse_pos.x < ent->rect.x + ent->rect.w && 
        input->mouse_pos.y > ent->rect.y && 
        input->mouse_pos.y < ent->rect.y + ent->rect.h){
            return 1;
    } else{
        return 0;
    }
}

void update_debug_tool(debug_tool_t* debug_tool, level_t* level, input_t* input){
    if (input->mouse_l_click){

        /*SELECT ENTITY*/
        if (debug_tool->selected_ent == NULL){
            for (int i = 0; i < level->ent_count; i++){
                if (mouse_ent_collision(input, level->ents[i])){
                    debug_tool->selected_ent = level->ents[i];
                    break;
                } 
            }

        /*SELECT VERTEX*/
        }else if (debug_tool->selected_vertex == -1){
            debug_tool->selected_vertex = select_vertex(input, debug_tool->selected_ent);

            /*select y offset*/
            select_y_offset(input, debug_tool, debug_tool->selected_ent);

            /*DESELECT ENTITY*/
            if (debug_tool->selected_vertex == -1 && !debug_tool->adjusting_y){
                if (!mouse_ent_collision(input, debug_tool->selected_ent)){
                    debug_tool->selected_ent = NULL;
                }
                
            /*DRAG Y OFFSET*/
            }else if (debug_tool->adjusting_y){
                debug_tool->selected_ent->colider->y_offset = input->mouse_pos.y-debug_tool->selected_ent->rect.y;
            }

        }else { //if ent and vertex selected
            /*DRAG VERTEX*/
            if (debug_tool->selected_vertex != -1){
                debug_tool->selected_ent->colider->vertex[debug_tool->selected_vertex].x = input->mouse_pos.x - debug_tool->selected_ent->rect.x;
                debug_tool->selected_ent->colider->vertex[debug_tool->selected_vertex].y = input->mouse_pos.y - debug_tool->selected_ent->rect.y;
            }

        }
    }else {
        /*DESELECT VERTEX*/
        debug_tool->selected_vertex = -1;
        debug_tool->adjusting_y = 0;
    }
}

void draw_debug (SDL_Renderer* renderer, debug_tool_t* debug_tool){
    if (debug_tool->selected_ent != NULL){
          draw_ent_outline(renderer, debug_tool->selected_ent);
          draw_colider(renderer, debug_tool->selected_ent->colider, (ivec2){debug_tool->selected_ent->rect.x, debug_tool->selected_ent->rect.y});
        }
}