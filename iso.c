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
#include "debug.h"


/*player char*/
SDL_Texture* pc_texture;
ivec2 pc_rect;
spritesheet* pss;
ivec2 pc_vel;

typedef struct mouse_ {
    ivec2 pos;
    unsigned int down :1;
    ent* selected;
    int vert_ind;
} mouse;



ivec2 mouse_pos;
unsigned int mouse_down = 0;

struct mouse_vert{
  colider* colider;
  int vert_index;
};

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
  mouse m1;
  m1.selected = NULL;
  m1.vert_ind = -1;


  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_Event event;

  SDL_Surface* dirt = SDL_LoadBMP("../res/tile1.bmp");
  SDL_Texture* dirt_t = SDL_CreateTextureFromSurface(renderer, dirt);

  ent* brick = init_ent((SDL_Rect){111, 0, 222, 256}, renderer, "../res/bricks.bmp");
  add_colider(brick);

  ent* brick2 = init_ent((SDL_Rect){333, 256, 222, 256}, renderer, "../res/bricks.bmp");
  add_colider(brick2);

  ent* ents[16];
  ents[0] = brick;
  ents[1] = brick2;
  int ent_count = 2;


  spritesheet* pc_ss_d = make_sprite(renderer, "../res/pc_ss_d.bmp", 14);
  spritesheet* pc_ss_dl = make_sprite(renderer, "../res/pc_ss_dl.bmp", 14);
  spritesheet* pc_ss_l = make_sprite(renderer, "../res/pc_ss_l.bmp", 14);
  spritesheet* pc_ss_ul = make_sprite(renderer, "../res/pc_ss_ul.bmp", 14);
  spritesheet* pc_ss_u = make_sprite(renderer, "../res/pc_ss_u.bmp", 14);
  spritesheet* pc_ss_ur = make_sprite(renderer, "../res/pc_ss_ur.bmp", 14);
  spritesheet* pc_ss_r = make_sprite(renderer, "../res/pc_ss_r.bmp", 14);
  spritesheet* pc_ss_dr = make_sprite(renderer, "../res/pc_ss_dr.bmp", 14);
  pss = pc_ss_d;

  colider* pc_c = make_colider(pc_ss_d);

  pc_rect.x = 200;
  pc_rect.y = 200;
  

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

  struct mouse_vert mv;
  mv.colider = NULL;
  mv.vert_index = -1;

  while (!(event.type == SDL_QUIT)){
    SDL_RenderClear(renderer); //Clear screen

    for (size_t i = 0; i < 32; i++){
      for (size_t j = 0; j < 32; j++){
        draw_m_sqr(renderer, map[i][j]);
      }
    }
    
    for (size_t i = 0; i < ent_count; i++){
      render_ent(renderer, ents[i]);
    }
    
      
      
      pc_vel.x = 0;
      pc_vel.y = 0;

      while( SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
          SDL_Quit();
        }else if (event.type == SDL_KEYDOWN){
          switch(event.key.keysym.sym){
            case SDLK_LEFT:
              pc_vel.x = -1;
              break;

            case SDLK_RIGHT:
              pc_vel.x = 1;
              break;

            case SDLK_UP:
              pc_vel.y = -1;
              break;

            case SDLK_DOWN:
              pc_vel.y = 1;
              break;

            case SDLK_ESCAPE:
              SDL_Quit();
              return 1;
              break;
          }
          
        }else if (event.type == SDL_MOUSEBUTTONDOWN){
          SDL_GetMouseState( &m1.pos.x, &m1.pos.y);
          mouse_down = 1;
          
          
          #if DEBUG
            /*ENT COLIDER VERTEX SELECTION*/
            if (m1.selected != NULL){
              m1.vert_ind = select_vertex(m1.selected->colider, (ivec2){m1.selected->rect.x, m1.selected->rect.y}, m1.pos);
            }

            /*ENT SELECTION*/
            if (m1.vert_ind == -1){
              for (int i = 0; i < ent_count; i++){
                if (m1.pos.x > ents[i]->rect.x && m1.pos.x < ents[i]->rect.x + ents[i]->rect.w){
                  if (m1.pos.y > ents[i]->rect.y && m1.pos.y < ents[i]->rect.y + ents[i]->rect.h){
                    m1.selected = ents[i];
                    break;
                  }
                }
                m1.selected = NULL;
              }
            }
            
          #endif

        
        }else if (event.type == SDL_MOUSEBUTTONUP){
          SDL_GetMouseState( &m1.pos.x, &m1.pos.y);
          mouse_down = 0;

          #if DEBUG
            /*MOVE AND DESELECT VERTEX*/
            if (m1.vert_ind != -1){
              m1.selected->colider->vertex[m1.vert_ind].x = m1.pos.x - m1.selected->rect.x;
              m1.selected->colider->vertex[m1.vert_ind].y = m1.pos.y - m1.selected->rect.y;
              m1.vert_ind = -1;
            }
          #endif
          
          
          
        }else if (event.type = SDL_MOUSEMOTION){
          SDL_GetMouseState( &m1.pos.x, &m1.pos.y);

          #if DEBUG
            /*MOVE VERTEX*/
            if (m1.vert_ind != -1){
              m1.selected->colider->vertex[m1.vert_ind].x = m1.pos.x - m1.selected->rect.x;
              m1.selected->colider->vertex[m1.vert_ind].y = m1.pos.y - m1.selected->rect.y;
            }
          #endif
          
        }
      }

      /*if (pc_vel.x != 0 || pc_vel.y != 0){
        printf("vel x: %d, y: %d \n", pc_vel.x, pc_vel.y);
      }*/
      

      pc_rect.x += pc_vel.x*SPEED;
      pc_rect.y += pc_vel.y*SPEED;

      if (pc_vel.x == 1){
        if (pc_vel.y == -1){
          pss = pc_ss_ur;
        }else if (pc_vel.y == 1){
          pss = pc_ss_dr;
        }else if (pc_vel.y == 0){
          pss = pc_ss_r;
        }
      }else if (pc_vel.x == -1){
        if (pc_vel.y == -1){
          pss = pc_ss_ul;
        }else if (pc_vel.y == 1){ 
          pss = pc_ss_dl;
        }else if (pc_vel.y == 0){
          pss = pc_ss_l;
        }
      }else if (pc_vel.x == 0){
        if (pc_vel.y == 1){
          pss = pc_ss_d;
        }else if (pc_vel.y == -1){
          pss = pc_ss_u;
        }
      }

      render(renderer, pss, pc_rect);
      #if DEBUG
        if (m1.selected != NULL){
          draw_ent_outline(renderer, m1.selected);
          draw_colider(renderer, m1.selected->colider, (ivec2){m1.selected->rect.x, m1.selected->rect.y});
        }
      #endif
      
      
      
      
    SDL_RenderPresent(renderer); //Render to window
  }//end of main game loop
}