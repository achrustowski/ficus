#ifndef PLAYER_H_
#define PLAYER_H_

#include "structs.h"

void player_init(Entity* player);
void player_draw(Entity* player);
void player_logic(Entity* player, Tile_Map* tile_map);

#endif
