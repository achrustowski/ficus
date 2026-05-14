#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "defs.h"
#include <string.h>
#include "game.h"
#include "debug.h"

App app;
static Game game;

int main()
{
    memset(&app, 0, sizeof(App));
    app.S_W = 1600;
    app.S_H = 900;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(app.S_W, app.S_H, "Game");

    // Custom timming variables
    double previous_time = GetTime();
    double current_time = 0.0;
    double update_draw_time = 0.0;
    double wait_time = 0.0;
    app.delta_time = 0.0f;

    //SetTargetFPS(FPS);
    int target_fps = 60;

    debug_menu_init(&app.debug_menu);
    game_init(&game);

    while(!WindowShouldClose())
    {
        app.delta_time = GetFrameTime();
        snprintf(app.debug_menu.frame_rate, sizeof(app.debug_menu.frame_rate), "FPS %.2f", (int)1.0f/app.delta_time);
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

        BeginMode2D(game.camera);
        game_draw(&game);
        EndMode2D();

        debug_menu_draw(&app.debug_menu);

        EndDrawing();

        current_time = GetTime();
        update_draw_time = current_time - previous_time;

        if (target_fps > 0)
        {
            wait_time = (1.0f/(float)target_fps) - update_draw_time;
            if (wait_time > 0.0f)
            {
                WaitTime((float)wait_time);
                current_time = GetTime();
                app.delta_time = (float)(current_time - previous_time);
            }
        } else
        {
            app.delta_time = (float)update_draw_time;
        }
        previous_time = current_time;

    }

    CloseWindow();

    return 0;
}
