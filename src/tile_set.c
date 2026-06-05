#include "tile_set.h"
#include "enums.h"
#include "raylib.h"
#include "stdlib.h"
#include "defs.h"
#include <stdio.h>

static void tile_set_init(Tile_Set* t_s, char* filename);
static void tile_set_init_layers(Stage* stage);

static void tile_set_init(Tile_Set* t_s, char* filename)
{
    t_s->texture = LoadTexture(filename);
    int columns = t_s->texture.width / TILE_SIZE;
    int rows = t_s->texture.height / TILE_SIZE;

    t_s->size = columns * rows;
    t_s->tiles = malloc(sizeof(Tile) * t_s->size);

    for (int i = 0; i < t_s->size; ++i)
    {
        int col = i % columns;
        int row = i / columns;
        t_s->tiles[i].rect = (Rectangle)
            {
                col * TILE_SIZE,
                row * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE
            };
    }
}

static void tile_set_init_layers(Stage* stage)
{
    stage->tile_map.layers[LAYER_GROUND].tile_set = &stage->tile_set_ground;
    stage->tile_map.layers[LAYER_DECORATIONS].tile_set = &stage->tile_set_terrain_objects;
}

void tile_set_load(Stage* stage)
{
    tile_set_init(&stage->tile_set_ground, "./assets/ground_tiles/Grass.png");
    tile_set_init(&stage->tile_set_terrain_objects, "./assets/ground_tiles/TerrainObjects.png");
    tile_set_init_layers(stage);
}
