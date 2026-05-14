#include "defs.h"
#include "raylib.h"
#include "structs.h"
#include "tilemap.h"
#include <stdlib.h>
#include <stdio.h>

extern App app;

void tile_map_init(Tile_Map* tile_map)
{
    tile_map->width = 512;
    tile_map->height = 512;
    tile_map->tiles = malloc(sizeof(int) * tile_map->width * tile_map->height);
}

void tile_map_assign(Tile_Map* tile_map, Tile_Set* tile_set)
{
    for (int y = 0; y < tile_map->height; ++y)
    {
        for (int x = 0; x < tile_map->width; ++x)
        {
            tile_map->tiles[y * tile_map->width + x] = rand() % tile_set->size;
        }
    }
}

void tile_map_draw(Game* game, Tile_Map* tile_map, Tile_Set* tile_set)
{
    float viewport_start_x = game->camera.target.x - game->camera.offset.x;
    float viewport_start_y = game->camera.target.y- game->camera.offset.y;
    float viewport_end_x = game->camera.target.x + game->camera.offset.x;
    float viewport_end_y = game->camera.target.y + game->camera.offset.y;

    int start_x = (game->camera.target.x - game->camera.offset.x) / TILE_SIZE;
    int start_y = (game->camera.target.y - game->camera.offset.y) / TILE_SIZE;
    int end_x = (game->camera.target.x + game->camera.offset.x) / TILE_SIZE + 1;
    int end_y = (game->camera.target.y + game->camera.offset.y) / TILE_SIZE + 1;

    for (int y = start_y; y < end_y; ++y)
    {
        for (int x = start_x; x < end_x; ++x)
        {
            int tile_id = tile_map->tiles[y * tile_map->width + x];
            tile_set->tiles[tile_id].rect.x = x * TILE_SIZE;
            tile_set->tiles[tile_id].rect.y = y * TILE_SIZE;
            DrawRectangleRec(tile_set->tiles[tile_id].rect, tile_set->tiles[tile_id].color);
        }
    }

    snprintf(app.debug_menu.screen_start, sizeof(app.debug_menu.screen_start), "START: %.2f, %.2f", viewport_start_x, viewport_start_y);
    snprintf(app.debug_menu.screen_end, sizeof(app.debug_menu.screen_end), "END: %.2f, %.2f", viewport_end_x, viewport_end_y);
}
