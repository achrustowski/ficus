#include "stage.h"
#include "player.h"
#include <string.h>
#include "tile_map.h"
#include "tile_set.h"
#include "dev_mode.h"

void stage_init(Stage* stage)
{
    player_init(&stage->player);
    tile_map_init(&stage->tile_map);
    tile_set_init(&stage->tile_set);
    tile_set_assign(&stage->tile_set);
    tile_map_assign(&stage->tile_map, &stage->tile_set);
}

void stage_logic(Game* game)
{
    player_logic(&game->stage.player, &game->stage.tile_map);
}

void stage_draw(Game* game)
{
    tile_map_draw(game, &game->stage.tile_map, &game->stage.tile_set);
    player_draw(&game->stage.player);
}
