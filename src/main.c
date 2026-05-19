#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>
#include "dev_mode.h"
#include "game.h"
#include "debug.h"
#include "defs.h"

App app;
Game game;

int main()
{
    memset(&app, 0, sizeof(App));
    app.S_W = 1600;
    app.S_H = 900;
    app.dev_mode_enabled = false;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(app.S_W, app.S_H, "Game");

    SetTargetFPS(FPS);

    dev_mode_init();
    debug_menu_init(&app.debug_menu);
    game_init(&game);

    while(!WindowShouldClose())
    {
        app.delta_time = GetFrameTime();
        snprintf(app.debug_menu.frame_rate, sizeof(app.debug_menu.frame_rate), "FPS %.2f", 1.0f/app.delta_time);
        if (IsWindowResized())
        {
            int w = GetScreenWidth();
            int h = GetScreenHeight();

            game.camera.offset = (Vector2){ w / 2.0f, h / 2.0f };
        }
        game_logic(&game);
        debug_menu_toggle(&app.debug_menu);

        BeginDrawing();
        ClearBackground(BLACK);

        game_draw(&game);

        debug_menu_draw(&app.debug_menu);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
