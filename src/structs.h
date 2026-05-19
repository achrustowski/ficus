#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <raylib.h>
#include "enums.h"

typedef struct Timer Timer;
typedef struct Entity Entity;
typedef struct Tile Tile;
typedef struct Tile_Map Tile_Map;
typedef struct Tile_Set Tile_Set;
typedef struct Stage Stage;
typedef struct Debug Debug;
typedef struct Dialog Dialog;

struct Timer
{
    double start_time;
    double life_time;
    bool started;
};

struct Entity
{
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

struct Tile
{
    Rectangle rect;
    Rectangle collision_box;
    Collision_Side collision_side;
    Color color;
};

struct Tile_Map
{
    int width;
    int height;
    int* tiles;
};

struct Tile_Set
{
    int size;
    Tile* tiles;
    Color* colors;
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
};

typedef struct Dialog_Manager
{
    int size;
    Dialog* dialogs;
} Dialog_Manager;

typedef struct App
{
    int S_W;
    int S_H;
    float delta_time;
    Debug debug_menu;
    bool dev_mode_enabled;
} App;

struct Stage
{
    Tile_Map tile_map;
    Tile_Set tile_set;
    Entity player;
};

typedef struct Game
{
    Camera2D camera;
    Stage stage;
} Game;

#endif
