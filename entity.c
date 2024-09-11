#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"
#include "sprite.h"
#include "colider.h"
#include "entity.h"

void add_colider(ent* ent){
    ent->colider = make_colider(ent->spritesheet);
}

int check_collision(ent e1, ent e2){
    SDL_Point p1, p2, p3, p4;

    for (int i = 0; i < e1.colider->vertex_count; i++){
        p1.x = e1.colider->vertex[i].x + e1.rect.x;
        p1.y = e1.colider->vertex[i].y + e1.rect.y;

        if (i == e1.colider->vertex_count - 1){
            p2.x = e1.colider->vertex[0].x + e1.rect.x;
            p2.y = e1.colider->vertex[0].y + e1.rect.y;
        }else {
            p2.x = e1.colider->vertex[i + 1].x + e1.rect.x;
            p2.y = e1.colider->vertex[i + 1].y + e1.rect.y;
        }

        for (int j = 0; j < e2.colider->vertex_count; j++){
            p3.x = e2.colider->vertex[j].x + e1.rect.x;
            p3.y = e2.colider->vertex[j].y + e1.rect.y;

            if (j == e2.colider->vertex_count - 1){
                p4.x = e2.colider->vertex[0].x + e1.rect.x;
                p4.y = e2.colider->vertex[0].y + e1.rect.y;
            }else {
                p4.x = e2.colider->vertex[j + 1].x + e1.rect.x;
                p4.y = e2.colider->vertex[j + 1].y + e1.rect.y;
            }

            if (check_intersection(p1, p2, p3, p4)){
                printf("Collision between ((%d, %d), (%d, %d)) and ((%d, %d), (%d, %d))\n", p1.x, p1.y,
                                                                                            p2.x, p2.y,
                                                                                            p3.x, p3.y,
                                                                                            p4.x, p4.y);
                return 1;
            }
        }
    }
    return 0;    
}

void y_sort_ents(ent** ents, int ent_count){
    for (int  i = 1; i < ent_count; i++){
        ent* switcher;
        int ent1y = ents[i-1]->colider->y_offset + ents[i-1]->rect.y;
        int ent2y = ents[i]->colider->y_offset + ents[i]->rect.y;
        if (ent1y > ent2y){
            switcher = ents[i-1];
            ents[i-1] = ents[i];
            ents[i] = switcher;
        }
    }
    
}


ent* init_ent(SDL_Rect rect, SDL_Renderer* renderer, spritesheet* spritesheet, const char* filepath){
    ent* new_ent = calloc(1, sizeof(ent));
    new_ent->vel = (SDL_Point){0,0};
    new_ent->rect = rect;
    new_ent->spritesheet_count = 0;

    if (filepath != NULL){
        new_ent->spritesheet = make_sprite(renderer, filepath, 0);
        new_ent->spritesheet_count += 1;

    }else if (spritesheet != NULL){
        new_ent->spritesheet = spritesheet;
        new_ent->spritesheet_count += 1;
    }
    add_colider(new_ent);
    return new_ent;
}

int render_ent(SDL_Renderer* renderer, ent* ent){
    render(renderer, ent->spritesheet, (SDL_Point){ent->rect.x, ent->rect.y});
    return 1;
}

int draw_ent_outline(SDL_Renderer* renderer, ent* ent){
    SDL_SetRenderDrawColor(renderer, 0, 0, 254, 0);
    SDL_RenderDrawRect(renderer, &ent->rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    return 1;
}
