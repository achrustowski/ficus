#include "player.h"
#include <stdio.h>
#include "defs.h"
#include "enums.h"
#include "raylib.h"

extern App app;
static Vector2 player_prev_position;

static void player_handle_input(Entity* player);
static void player_do_movement_x(Entity* player);
static void player_do_movement_y(Entity* player);
static void player_do_collisions_x(Entity* player, Tile_Map* tile_map);
static void player_do_collisions_y(Entity* player, Tile_Map* tile_map);

void player_init(Entity* player)
{
    player->rect = (Rectangle){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, PLAYER_WIDTH, PLAYER_HEIGHT};
    player->velocity = (Vector2){PLAYER_VELOCITY_X, PLAYER_VELOCITY_Y};
    player->color = WHITE;
    player->speed = (Vector2){PLAYER_SPEED_X, PLAYER_SPEED_Y};
    player->collision_side = P_NONE;
    player->movement_direction_x = 0;
    player->movement_direction_y = 0;
}

void player_logic(Entity* player, Tile_Map* tile_map)
{
    player_handle_input(player);
    player_do_movement_x(player);
    player_do_collisions_x(player, tile_map);
    player_do_movement_y(player);
    player_do_collisions_y(player, tile_map);
}

static void player_handle_input(Entity* player)
{
    player->movement_direction_x = 0;
    player->movement_direction_y = 0;
    if (IsKeyDown(KEY_D))
    {
        player->movement_direction_x = 1;
    }
    if (IsKeyDown(KEY_A))
    {
        player->movement_direction_x = -1;
    }
    if (IsKeyDown(KEY_W))
    {
        player->movement_direction_y = -1;
    }
    if (IsKeyDown(KEY_S))
    {
        player->movement_direction_y = 1;
    }
    if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) { player->movement_direction_x = 0; }
    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_S)) { player->movement_direction_y = 0; }
}

static void player_do_movement_x(Entity* player)
{
    player->velocity.x = player->movement_direction_x * player->speed.x;
    player->rect.x += player->velocity.x * app.delta_time;
}

static void player_do_movement_y(Entity* player)
{
    player->velocity.y = player->movement_direction_y * player->speed.y;
    player->rect.y += player->velocity.y * app.delta_time;
}

static void player_do_collisions_x(Entity* player, Tile_Map* tile_map)
{
    if (player->rect.x < PLAYER_WIDTH / 2.0f)
    {
        player->rect.x = PLAYER_WIDTH / 2.0f;
    } else if (player->rect.x > tile_map->width * TILE_SIZE - PLAYER_WIDTH / 2.0f)
    {
        player->rect.x = tile_map->width * TILE_SIZE - PLAYER_WIDTH / 2.0f;
    }
}
static void player_do_collisions_y(Entity* player, Tile_Map* tile_map)
{
    if (player->rect.y < PLAYER_HEIGHT / 2.0f)
    {
        player->rect.y = PLAYER_HEIGHT / 2.0f;
    } else if (player->rect.y > tile_map->height * TILE_SIZE - PLAYER_HEIGHT / 2.0f)
    {
        player->rect.y = tile_map->height * TILE_SIZE - PLAYER_HEIGHT / 2.0f;
    }
}

void player_draw(Entity* player)
{
    DrawRectangle(player->rect.x - PLAYER_WIDTH / 2.0f, player->rect.y - PLAYER_HEIGHT / 2.0f,
                  player->rect.width, player->rect.height, player->color);
}
