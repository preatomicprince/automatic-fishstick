#include "sprite.h"

SDL_Texture* make_texture(SDL_Renderer* renderer, const char* filepath){
    SDL_Surface* new_surface = SDL_LoadBMP(filepath);
    SDL_Texture* new_texture = SDL_CreateTextureFromSurface(renderer, new_surface);
    SDL_FreeSurface(new_surface);
    return new_texture;
}

spritesheet* make_sprite(SDL_Renderer* renderer, const char* filepath, int framecount){
    SDL_Surface* new_surface = SDL_LoadBMP(filepath);

    if (new_surface == NULL){
        printf("FAILED TO LOAD BMP! \n");
    }

    SDL_Texture* new_texture = SDL_CreateTextureFromSurface(renderer, new_surface);
    ivec2 new_size = {new_surface->w, new_surface->h};
    spritesheet new_spritesheet = {new_texture, framecount, 0, new_size};

    spritesheet* spritesheet_ptr = calloc(1, sizeof(spritesheet));

    spritesheet_ptr[0] = new_spritesheet;

    SDL_FreeSurface(new_surface);
    return spritesheet_ptr;
}

int render(SDL_Renderer* renderer, spritesheet* spritesheet, ivec2 pos){
    SDL_Rect sheet_rect = {pos.x, pos.y, spritesheet->size.x, spritesheet->size.y};
    
    
    if (spritesheet->frame_count == 0){
        SDL_RenderCopy(renderer, spritesheet->texture, NULL, &sheet_rect);
    } else {
        int frame_w = spritesheet->size.x/spritesheet->frame_count;

        sheet_rect.w = frame_w;

        int frame_x = frame_w*spritesheet->current_frame;

        SDL_Rect frame_rect = {frame_x, 0, frame_w, sheet_rect.h};

        SDL_RenderCopy(renderer, spritesheet->texture, &frame_rect, &sheet_rect);

        int ticks = SDL_GetTicks();
        spritesheet->current_frame = (ticks/60) % spritesheet->frame_count;
    }

    return 1;
}