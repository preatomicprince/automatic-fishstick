#pragma once

#define HEIGHT 600
#define WIDTH 800

#define SQRT3 1.732

#define Y_SPEED 0.2
#define X_SPEED Y_SPEED*SQRT3
#define VERT_SIZE 16 //Screen size of square over colison verticies

#define DEBUG 1 // 1 if on

/*typedefs*/

typedef struct fvec2_s {float x, y;} fvec2_t;
