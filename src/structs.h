#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <raylib.h>
#include "enums.h"

typedef struct Timer Timer;
typedef struct Entity Entity;
typedef struct Layer Layer;
typedef struct Tile Tile;
typedef struct Tile_Map Tile_Map;
typedef struct Tile_Set Tile_Set;
typedef struct Stage Stage;
typedef struct Debug Debug;
typedef struct Dialog Dialog;
typedef struct Dev Dev;

struct Timer
{
    double start_time;
    double life_time;
    bool started;
};

struct Entity
{
    Texture2D texture;
    Rectangle rect;
    Vector2 velocity;
    Vector2 speed;
    Color color;
    Side collision_side;
    int movement_direction_x;
    int movement_direction_y;
    Entity* next;
};

struct Dialog
{
    Rectangle rect;
    char text[64];
    char box_title[24];
    char button_title[12];
    bool is_active;
};

typedef struct Dialog_Manager
{
    int size;
    Dialog* dialogs;
} Dialog_Manager;

struct Layer
{
    int* tiles;
    int width;
    int height;
    Tile_Set* tile_set;
};

struct Tile
{
    Rectangle rect;
    Rectangle collision_box;
    Collision_Side collision_side;
};

struct Tile_Map
{
    int layer_count;
    int width;
    int height;
    Layer* layers;
};

struct Tile_Set
{
    int size;
    Tile* tiles;
    Texture2D texture;
};

struct Debug
{
    Rectangle rect;
    Color color;
    bool is_visible;
    char camera_text[64];
    char player_text[64];
    char camera_zoom[64];
    char screen_start[64];
    char screen_end[64];
    char frame_rate[32];
    char tiles_drawn[32];
};

struct Dev
{
    bool enabled;
    int selected_tile_id;
    int selected_tile_layer;
    Tile_Set* selected_tile_set;
    Rectangle tile_rect;
    bool mouse_over;
};

typedef struct App
{
    int S_W;
    int S_H;
    float delta_time;
    Debug debug_menu;
    Dev dev_mode;
} App;

struct Stage
{
    Tile_Map tile_map;
    Tile_Set tile_set_ground;
    Tile_Set tile_set_terrain_objects;
    Entity player;
};

typedef struct Game
{
    Camera2D camera;
    Stage stage;
} Game;

#endif
