#include "defs.h"
#include "enums.h"
#include "raylib.h"
#include "structs.h"
#include "tile_map.h"
#include <stdlib.h>
#include <stdio.h>

extern App app;

static void tile_map_save(Stage* stage);
static void tile_map_load(Stage* stage);

void tile_map_init(Tile_Map* tile_map)
{
    tile_map->width = 512;
    tile_map->height = 512;
    tile_map->layer_count = 2;
    tile_map->layers = malloc(sizeof(Layer) * tile_map->layer_count);
    for (int i = 0; i < tile_map->layer_count; ++i)
    {
        tile_map->layers[i].tiles = malloc(sizeof(int) * tile_map->width * tile_map->height);
    }
}

void tile_map_reassign(Stage* s, int width, int height)
{
    if (width >= 50 && height >= 50)
    {
        s->tile_map.width = width;
        s->tile_map.height = height;

        for (int i = 0; i < s->tile_map.layer_count; ++i)
        {
            int* tmp = realloc(s->tile_map.layers[i].tiles, sizeof(int) * s->tile_map.width * s->tile_map.height);

            if (tmp != NULL)
                s->tile_map.layers[i].tiles = tmp;
        }
        tile_map_save(s);
        tile_map_assign(&s->tile_map);
        tile_map_load(s);
    }
}

void tile_map_assign(Tile_Map* tile_map)
{
    for (int y = 0; y < tile_map->height; ++y)
    {
        for (int x = 0; x < tile_map->width; ++x)
        {
            int i = y * tile_map->width + x;
            tile_map->layers[LAYER_GROUND].tiles[i] = 0;
            tile_map->layers[LAYER_DECORATIONS].tiles[i] = -1;
        }
    }
}

void tile_map_paint(Game* game)
{
    Vector2 world_pos = GetScreenToWorld2D(GetMousePosition(), game->camera);

    int x = world_pos.x / TILE_SIZE;
    int y = world_pos.y / TILE_SIZE;

    if (x < 0 || x >= game->stage.tile_map.width) return;
    if (y < 0 || y >= game->stage.tile_map.height) return;

    int index = y * game->stage.tile_map.width + x;

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !app.dev_mode.mouse_over)
    {
        game->stage.tile_map.layers[app.dev_mode.selected_tile_layer].tiles[index] = app.dev_mode.selected_tile_id;
    }
}

void tile_map_draw(Game* game, Stage* stage)
{
    int tiles_drawn = 0;

    float half_w = game->camera.offset.x / game->camera.zoom;
    float half_h = game->camera.offset.y / game->camera.zoom;

    // Calculates world space coordinates of the viewport edges
    float world_start_x = game->camera.target.x - half_w;
    float world_start_y = game->camera.target.y - half_h;
    float world_end_x   = game->camera.target.x + half_w;
    float world_end_y   = game->camera.target.y + half_h;

    // Converts world coordinates to tile indices
    int start_x = (int)(world_start_x / TILE_SIZE);
    int start_y = (int)(world_start_y / TILE_SIZE);
    int end_x   = (int)(world_end_x   / TILE_SIZE) + 1;
    int end_y   = (int)(world_end_y   / TILE_SIZE) + 1;

    // Prevents out of bounds array access
    start_x = CLAMP(start_x, 0, stage->tile_map.width);
    start_y = CLAMP(start_y, 0, stage->tile_map.height);
    end_x   = CLAMP(end_x,   0, stage->tile_map.width);
    end_y   = CLAMP(end_y,   0, stage->tile_map.height);

    for (int i = 0; i < stage->tile_map.layer_count; ++i)
    {
        Tile_Set* current_layer = stage->tile_map.layers[i].tile_set;
        for (int y = start_y; y < end_y; ++y)
        {
            for (int x = start_x; x < end_x; ++x)
            {
                int tile_id = stage->tile_map.layers[i].tiles[y * stage->tile_map.width + x];
                if (tile_id < 0) continue;
                Rectangle rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                DrawTextureRec(current_layer->texture, current_layer->tiles[tile_id].rect, (Vector2){rect.x, rect.y}, WHITE);
                tiles_drawn++;
            }
        }
    }

    if (app.dev_mode.enabled)
    {
        Vector2 mouse_pos = GetScreenToWorld2D(GetMousePosition(), game->camera);

        int mouse_x = ((int)mouse_pos.x / TILE_SIZE) * TILE_SIZE;
        int mouse_y = ((int)mouse_pos.y / TILE_SIZE) * TILE_SIZE;

        DrawRectangleLines(mouse_x, mouse_y, TILE_SIZE, TILE_SIZE, RED);
    }

    snprintf(app.debug_menu.screen_start, sizeof(app.debug_menu.screen_start),
                "START: %.2f, %.2f", world_start_x, world_start_y);
    snprintf(app.debug_menu.screen_end, sizeof(app.debug_menu.screen_end),
                "END: %.2f, %.2f", world_end_x, world_end_y);
    snprintf(app.debug_menu.tiles_drawn, sizeof(app.debug_menu.tiles_drawn),
                "TILES: %d", tiles_drawn);
}

static void tile_map_save(Stage* stage)
{
    FILE* f = fopen("tiles.txt", "wb");

    for (int y = 0; y < stage->tile_map.height; ++y)
    {
        for (int x = 0; x < stage->tile_map.width; ++x)
        {
            int index = y * stage->tile_map.width + x;
            fprintf(f, "%d\n", stage->tile_map.layers[app.dev_mode.selected_tile_layer].tiles[index]);
        }
    }
    fclose(f);
}

static void tile_map_load(Stage* stage)
{
    FILE* f = fopen("tiles.txt", "r");

    for (int y = 0; y < stage->tile_map.height; ++y)
    {
        for (int x = 0; x < stage->tile_map.width; ++x)
        {
            int index = y * stage->tile_map.width + x;
            fscanf(f, "%d\n", &stage->tile_map.layers[app.dev_mode.selected_tile_layer].tiles[index]);
        }
    }
    fclose(f);
}

void tile_map_save_load(Game* game)
{
    if (IsKeyPressed(KEY_K))
    {
        tile_map_save(&game->stage);
    }
    if (IsKeyPressed(KEY_L))
    {
        tile_map_load(&game->stage);
    }
}
