#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "input.h"
#include "sprite.h"
#include "settings.h"

#include "entity.h"
#include "level.h"
#include "player.h"

player_t* init_player(SDL_Renderer* renderer){
    player_t* new_player = calloc(1, sizeof(player_t));
    load_player_textures(renderer, new_player);
    new_player->ent = init_ent((SDL_Rect){500, 0, 128, 128}, renderer, new_player->spritesheets[0], NULL);
    new_player->pos.x = new_player->ent->rect.x;
    new_player->pos.y = new_player->ent->rect.y;

    return new_player;
}

int player_col(player_t* player, ent** ents, int ent_count){
    for (int i = 0; i < ent_count; i++){
        // Temp. Need to add id to ent for comparison
        if (player->ent->rect.x != ents[i]->rect.x && player->ent->rect.x != ents[i]->rect.x){
            continue;
        }

        if (check_collision(*player->ent, *ents[i])){
            player->vel.x = -player->vel.x;
            player->vel.y = -player->vel.y;
        }
    }
}

void update_player(player_t* player, input_t* input, level_t level){
    int sprite_index;

    if (input->key_left){
        player->vel.x += -1;
    }
    if (input->key_right){
        player->vel.x += 1;
    }
    if (input->key_up){
        player->vel.y += -1;
    }
    if (input->key_down){
        player->vel.y += 1;
    }

    //player_col(player, level.ents, level.ent_count);

    player->pos.x += player->vel.x*X_SPEED;
    player->pos.y += player->vel.y*Y_SPEED;

    player->ent->rect.x = (int){player->pos.x};
    player->ent->rect.y = (int){player->pos.y};

    if (player->vel.x == 1){
        if (player->vel.y == 1){
            player->ent->spritesheet = player->spritesheets[7];
        }else if (player->vel.y == -1){
            player->ent->spritesheet = player->spritesheets[5];
        }else if (player->vel.y == 0){
            player->ent->spritesheet = player->spritesheets[6];
        }

    }else if (player->vel.x == -1){
        if (player->vel.y == 1){
            player->ent->spritesheet = player->spritesheets[1];
        }else if (player->vel.y == -1){
            player->ent->spritesheet = player->spritesheets[3];
        }else if (player->vel.y == 0){
            player->ent->spritesheet = player->spritesheets[2]; 
        }

    }else if (player->vel.x == 0){
        if (player->vel.y == 1){
            player->ent->spritesheet = player->spritesheets[0];
        }else if (player->vel.y == -1){
            player->ent->spritesheet = player->spritesheets[4];
        }else if (player->vel.y == 0){
            //idle needs implementing. Maybe just keep direction order and add 8
            player->ent->spritesheet = player->spritesheets[0];
        }
    }else{
        player->ent->spritesheet = player->spritesheets[0]; //just incase
    }

    player->vel = (SDL_Point){0, 0};
}

void load_player_textures(SDL_Renderer* renderer, player_t* player){
    spritesheet* newsprite0 = calloc(1, sizeof(spritesheet));

    player->spritesheets[0] = make_sprite(renderer, "../res/pc_ss_d.bmp", 14);
    player->spritesheets[1] = make_sprite(renderer, "../res/pc_ss_dl.bmp", 14);
    player->spritesheets[2] = make_sprite(renderer, "../res/pc_ss_l.bmp", 14);
    player->spritesheets[3] = make_sprite(renderer, "../res/pc_ss_ul.bmp", 14);
    player->spritesheets[4] = make_sprite(renderer, "../res/pc_ss_u.bmp", 14);
    player->spritesheets[5] = make_sprite(renderer, "../res/pc_ss_ur.bmp", 14);
    player->spritesheets[6] = make_sprite(renderer, "../res/pc_ss_r.bmp", 14);
    player->spritesheets[7] = make_sprite(renderer, "../res/pc_ss_dr.bmp", 14);
}

int render_player(SDL_Renderer* renderer, player_t* player){
    render(renderer, player->ent->spritesheet, (SDL_Point){player->ent->rect.x, player->ent->rect.y});
    return 1;
}