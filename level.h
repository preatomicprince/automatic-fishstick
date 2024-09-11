#ifndef LEVEL
#define LEVEL

#include "entity.h"

typedef struct level_s{
  ent* ents[64];
  int ent_count;
}level_t;

#endif