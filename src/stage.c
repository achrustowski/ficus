#include "stage.h"
#include "player.h"
#include <string.h>
#include "tile_map.h"
#include "tile_set.h"

void stage_init(Stage* stage)
{
    player_init(&stage->player);
    tile_map_init(&stage->tile_map);
    tile_set_load(stage);
    tile_map_assign(&stage->tile_map);
}

void stage_logic(Game* game)
{
    player_logic(&game->stage.player, &game->stage.tile_map);
    tile_map_paint(game);
    tile_map_save_load(game);
}

void stage_draw(Game* game)
{
    tile_map_draw(game, &game->stage);
    player_draw(&game->stage.player);
}
