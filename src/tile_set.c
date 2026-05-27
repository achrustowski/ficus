#include "tile_set.h"
#include "defs.h"
#include "raylib.h"
#include "stdlib.h"
#include "tiles.h"

void tile_set_init(Tile_Set* tile_set)
{
    tile_set->size = 14;
    tile_set->tiles = malloc(sizeof(Tile) * tile_set->size);
    tile_set->colors = malloc(sizeof(Color) * tile_set->size);
    tile_set->tiles[0] = tile_create(TILE_SIZE, TILE_SIZE, 0, BROWN);
}

void tile_set_assign(Tile_Set *tile_set)
{
    tile_set->colors[0] = PINK;
    tile_set->colors[1] = GRAY;
    tile_set->colors[2] = GREEN;
    tile_set->colors[3] = YELLOW;
    tile_set->colors[4] = GOLD;
    tile_set->colors[5] = ORANGE;
    tile_set->colors[6] = PINK;
    tile_set->colors[7] = RED;
    tile_set->colors[8] = MAROON;
    tile_set->colors[9] = LIME;
    tile_set->colors[10] = BLUE;
    tile_set->colors[11] = PURPLE;
    tile_set->colors[12] = MAGENTA;
    tile_set->colors[13] = BROWN;

        for (int i = 0; i < tile_set->size; ++i)
        {
            tile_set->tiles[i] = tile_set->tiles[0];
        }
}
