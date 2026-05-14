#include "raylib.h"
#include "defs.h"
#include "structs.h"
#include "misc.h"

void clamp(Vector2* pos, Tile_Map* tile_map)
{
    if (pos->x < GetScreenWidth() / 2.0f)
    {
        pos->x = GetScreenWidth() / 2.0f;
    } else if (pos->x > tile_map->width * TILE_SIZE - GetScreenWidth() / 2.0f)
    {
        pos->x = tile_map->width * TILE_SIZE - GetScreenWidth() / 2.0f;
    }
    if (pos->y < GetScreenHeight() / 2.0f)
    {
        pos->y = GetScreenHeight() / 2.0f;
    } else if (pos->y > tile_map->width * TILE_SIZE - GetScreenHeight() / 2.0f)
    {
        pos->y = tile_map->width * TILE_SIZE - GetScreenHeight() / 2.0f;
    }
}
