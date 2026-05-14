#include "debug.h"
#include "raylib.h"
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

void debug_menu_init(Debug* debug)
{
    debug->rect.x = 0.0f;
    debug->rect.y = 0.0f;
    debug->rect.width = DEBUG_WIDTH;
    debug->rect.height = DEBUG_HEIGHT;
    debug->is_visible = true;
}

void debug_menu_toggle(Debug *debug)
{
    if (IsKeyPressed(KEY_Q))
    {
        if (debug->is_visible) debug->is_visible = false;
        else debug->is_visible = true;
    }
}

void debug_menu_draw(Debug* debug)
{
    if (debug->is_visible)
    {
        DrawRectangleRec(debug->rect, ColorAlpha(DARKBLUE, 0.8f));
        DrawText(debug->player_text, debug->rect.x + 10.0f, debug->rect.y + 10.0f, 20, GREEN);
        DrawText(debug->camera_text, debug->rect.x + 10.0f, debug->rect.y + 50.0f, 20, GREEN);
        DrawText(debug->camera_zoom, debug->rect.x + 10.0f, debug->rect.y + 90.0f, 20, GREEN);
        DrawText(debug->screen_start, debug->rect.x + 10.0f, debug->rect.y + 130.0f, 20, GREEN);
        DrawText(debug->screen_end, debug->rect.x + 10.0f, debug->rect.y + 170.0f, 20, GREEN);
        DrawText(debug->frame_rate, debug->rect.x + 10.0f, debug->rect.y + 210.0f, 20, GREEN);
    }
}
