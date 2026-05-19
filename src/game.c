#include "game.h"
#include "camera.h"
#include "raylib.h"
#include "stage.h"
#include "dev_mode.h"

void game_init(Game* game)
{
    camera_init(&game->camera);
    stage_init(&game->stage);
}

void game_logic(Game* game)
{
    stage_logic(game);
    camera_update(&game->stage, &game->camera);
    dev_mode_logic();
}

void game_draw(Game* game)
{
    BeginMode2D(game->camera);
    stage_draw(game);
    EndMode2D();
    dev_mode_draw();
}
