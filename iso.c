#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "settings.h"
#include "sprite.h"
#include "colider.h"
#include "entity.h"
#include "input.h"
#include "level.h"
#include "player.h"

#include "debug.h"


/*map*/
typedef struct m_sqr_{ //individual map squares
  int id;
  SDL_Texture* texture;
  SDL_Rect rect;
}m_sqr;

m_sqr m_sqr_init(SDL_Texture* texture, ivec2 pos, ivec2 size){
  m_sqr new_sqr;
  
  new_sqr.texture = texture;

  new_sqr.id = 0;

  new_sqr.rect.x = pos.x;
  new_sqr.rect.y = pos.y;

  new_sqr.rect.w = size.x;
  new_sqr.rect.h = size.y;

  return new_sqr;
}

int draw_m_sqr(SDL_Renderer* renderer, m_sqr square){
  SDL_RenderCopy(renderer, square.texture, NULL, &square.rect);
  return 0;
}

m_sqr map[32][32];

/*>>>>> MAIN <<<<<*/
int main() {
  SDL_Renderer* renderer = NULL;
  SDL_Window* window = NULL;

  input_t input;
  input.mouse_l_click = 0;

  #if DEBUG

  debug_tool_t debug_tool;
  debug_tool.selected_ent = NULL;
  debug_tool.selected_vertex = -1;

  #endif
  
  level_t level;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_Event event;

  SDL_Surface* dirt = SDL_LoadBMP("../res/tile1.bmp");
  SDL_Texture* dirt_t = SDL_CreateTextureFromSurface(renderer, dirt);

  ent* brick = init_ent((SDL_Rect){111, 0, 222, 256}, renderer, "../res/bricks.bmp");

  ent* brick2 = init_ent((SDL_Rect){333, 256, 222, 256}, renderer, "../res/bricks.bmp");

  player_t* player = init_player(renderer);

  level.ents[0] = brick;
  level.ents[1] = brick2;
  level.ent_count = 2;

  level.ents[2] = player->ent;
  level.ent_count += 1;

  for (int i = 0; i < 32; i++){
    for (int j = 0; j < 32; j++){
      ivec2 new_size = {222, 128};

      ivec2 new_pos;

      if (j%2){ //if even
        ivec2 new_pos = {i*222, j*64 };
      } else{
        ivec2 new_pos = {i*222 + 111, j*64};
      }

      map[i][j] = m_sqr_init(dirt_t, new_pos, new_size);
    }
  }
  
 /******************
 * MAIN GAME LOOP *
 * ^^^^ ^^^^ ^^^^ *
 ******************/

  while (!(event.type == SDL_QUIT)){
    SDL_RenderClear(renderer); //Clear screen      

      while( SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
          SDL_Quit();
        } else{
          handle_input(event, &input);
        }
      }
      
      #if DEBUG

      update_debug_tool(&debug_tool, &level, &input);

      #endif

      update_player(player, &input);
      y_sort_ents(level.ents, level.ent_count);


      for (size_t i = 0; i < 32; i++){
        for (size_t j = 0; j < 32; j++){
          draw_m_sqr(renderer, map[i][j]);
        }
      }
      
      for (size_t i = 0; i < level.ent_count; i++){
        render_ent(renderer, level.ents[i]);
      }

      #if DEBUG

      draw_debug(renderer, &debug_tool);

      #endif
            
    SDL_RenderPresent(renderer); //Render to window
  }//end of main game loop
}