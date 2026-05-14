#include "game.h"
#include "camera.h"
#include "stage.h"

void game_init(Game* game)
{
    camera_init(&game->camera);
    stage_init(&game->stage);
}

void game_logic(Game* game)
{
    stage_logic(game);
    camera_update(&game->stage, &game->camera);
}

void game_draw(Game* game)
{
    stage_draw(game);
}
