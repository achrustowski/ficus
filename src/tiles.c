#include "tiles.h"
#include "enums.h"
#include <raylib.h>

Tile tile_create(int width, int height, Collision_Side collision_side, Color color)
{
    Tile tile;
    tile.rect.x = 0.0f;
    tile.rect.y = 0.0f;
    tile.rect.width = width;
    tile.rect.height = height;
    tile.collision_box = (Rectangle){tile.rect.x, tile.rect.y, width, height};
    tile.color = color;

    return tile;
}

void tile_clear(Tile tile);
void tile_replace(Tile t1, Tile t2);
void tile_draw(Tile tile)
{
    DrawRectangleRec(tile.rect, tile.color);
}
