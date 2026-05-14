#ifndef TILE_H_
#define TILE_H_

#include "structs.h"

Tile tile_create(int width, int height, Collision_Side collision_side, Color color);
void tile_init(void);
void tile_clear(Tile tile);
void tile_replace(Tile t1, Tile t2);
void tile_draw(Tile tile);

#endif
