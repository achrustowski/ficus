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
    app.dev_mode.enabled = false;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(app.S_W, app.S_H, "Game");
    SetTargetFPS(FPS);

    game_init(&game);
    dev_mode_init();
    debug_menu_init(&app.debug_menu);

    double accumulator = 0.0;
    double fixed_step = 1.0 / 60.0;

    while (!WindowShouldClose())
    {
        accumulator += GetFrameTime();
        while (accumulator >= fixed_step)
        {
            app.delta_time = fixed_step;
            game_logic(&game);
            accumulator -= fixed_step;
        }

        snprintf(app.debug_menu.frame_rate, sizeof(app.debug_menu.frame_rate),
                 "FPS %.2f", 1.0f / GetFrameTime());

        if (IsWindowResized())
            game.camera.offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

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
