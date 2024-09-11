#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"
#include "sprite.h"
#include "colider.h"

SDL_Point add_p(SDL_Point p1, SDL_Point p2){
    return (SDL_Point){p1.x + p2.x, p1.y + p2.y};
}

//check if three ordered points are counterclockise
int ccw(SDL_Point p1, SDL_Point p2, SDL_Point p3){
    return (p3.y - p1.y)*(p2.x - p1.x) > (p2.y - p1.y)*(p3.x - p1.x); // stolen from https://bryceboe.com/2006/10/23/line-segment-intersection-algorithm/
}

int check_intersection(SDL_Point p1, SDL_Point p2, 
                        SDL_Point p3, SDL_Point p4){ //ibid.
    return ccw(p1, p3, p4) != ccw(p2, p3, p4) && ccw(p1, p2, p2) != ccw(p1, p2, p3);
}

colider* make_colider(spritesheet* spritesheet){
    colider* new_colider = calloc(1, sizeof(colider));
    if (spritesheet != NULL){
        new_colider->vertex[0] = (SDL_Point){0,0};
        new_colider->vertex[1] = (SDL_Point){spritesheet->size.x/(spritesheet->frame_count+1),0};
        new_colider->vertex[2] = (SDL_Point){spritesheet->size.x/(spritesheet->frame_count+1), spritesheet->size.y};
        new_colider->vertex[3] = (SDL_Point){0, spritesheet->size.y};
    }else{
        new_colider->vertex[0] = (SDL_Point){0,0};
        new_colider->vertex[1] = (SDL_Point){100,0};
        new_colider->vertex[2] = (SDL_Point){100, 100};
        new_colider->vertex[3] = (SDL_Point){0, 100};
    }
    
    new_colider->vertex_count = 4;
    new_colider->is_convex = 1;
    new_colider->active = 1; 
    new_colider->y_offset = spritesheet->size.y;

    return new_colider;
}

int draw_colider(SDL_Renderer* renderer, colider* colider, SDL_Point pos){
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
        SDL_Point v1, v2;
        v1 = (SDL_Point){colider->vertex[i].x + pos.x, colider->vertex[i].y+pos.y};
        if (i+1 < colider->vertex_count){
            v2 = (SDL_Point){colider->vertex[i+1].x + pos.x, colider->vertex[i+1].y+pos.y};
        } else{
            v2 = (SDL_Point){colider->vertex[0].x + pos.x, colider->vertex[0].y+pos.y};
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