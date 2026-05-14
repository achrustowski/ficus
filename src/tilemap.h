#ifndef TILE_MAP_H_
#define TILE_MAP_H_

#include "tilemap.h"

void tile_map_init(Tile_Map* tile_map);
void tile_map_assign(Tile_Map* tile_map, Tile_Set* tile_set);
void tile_map_draw(Game* game, Tile_Map* tile_map, Tile_Set* tile_set);

#endif
