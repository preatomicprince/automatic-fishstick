#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"
#include "sprite.h"
#include "colider.h"

colider* make_colider(spritesheet* spritesheet){
    colider* new_colider = calloc(1, sizeof(colider));
    if (spritesheet != NULL){
        new_colider->vertex[0] = (ivec2){0,0};
        new_colider->vertex[1] = (ivec2){spritesheet->size.x/(spritesheet->frame_count+1),0};
        new_colider->vertex[2] = (ivec2){spritesheet->size.x/(spritesheet->frame_count+1), spritesheet->size.y};
        new_colider->vertex[3] = (ivec2){0, spritesheet->size.y};
    }else{
        new_colider->vertex[0] = (ivec2){0,0};
        new_colider->vertex[1] = (ivec2){100,0};
        new_colider->vertex[2] = (ivec2){100, 100};
        new_colider->vertex[3] = (ivec2){0, 100};
    }
    
    new_colider->vertex_count = 4;
    new_colider->is_convex = 1;
    new_colider->active = 1; 
    new_colider->y_offset = spritesheet->size.y;

    return new_colider;
}

int draw_colider(SDL_Renderer* renderer, colider* colider, ivec2 pos){
    if  (colider->vertex_count < 3){
        printf("/n WARNING: Failed to draw colider. Too few vertices\n");
        return 0;
    }
    if (!colider->is_convex){
        printf(("\n WARNING: Failed to draw colider. Not convex \n"));
        return 0;
    }
    if (colider->active){
        SDL_SetRenderDrawColor(renderer, 0, 254, 0, 0);
    } else{
        SDL_SetRenderDrawColor(renderer, 254, 0, 0, 0);
    }

    for (int i = 0; i < colider->vertex_count; i++){
        ivec2 v1, v2;
        v1 = (ivec2){colider->vertex[i].x + pos.x, colider->vertex[i].y+pos.y};
        if (i+1 < colider->vertex_count){
            v2 = (ivec2){colider->vertex[i+1].x + pos.x, colider->vertex[i+1].y+pos.y};
        } else{
            v2 = (ivec2){colider->vertex[0].x + pos.x, colider->vertex[0].y+pos.y};
        }
        
        
        SDL_RenderDrawLine(renderer, v1.x, v1.y, v2.x, v2.y);

        SDL_Rect vrect = {v1.x-VERT_SIZE/2, v1.y-VERT_SIZE/2, VERT_SIZE, VERT_SIZE};
        SDL_RenderFillRect(renderer, &vrect);
    }

    SDL_SetRenderDrawColor(renderer, 254, 0, 0, 0);

    int y = pos.y + colider->y_offset;

    SDL_RenderDrawLine(renderer, 0, y, 1000, y);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    return 1;
}