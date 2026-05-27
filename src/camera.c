#include <raylib.h>
#include <string.h>
#include "camera.h"
#include <math.h>
#include <stdio.h>
#include "misc.h"

extern App app;

void camera_init(Camera2D* camera)
{
    camera->target = (Vector2) {0.0f, 0.0f};
    camera->offset = (Vector2)
        {
            GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f
        };
    camera->rotation = 0.0f;
    camera->zoom = 2.0f;
}

void camera_update(Stage* stage, Camera2D* camera)
{
    camera->target = (Vector2){
        (int)stage->player.rect.x,
        (int)stage->player.rect.y
    };
    camera->zoom = expf(logf(camera->zoom) + (float)(GetMouseWheelMove() * 0.1f));
    if (IsKeyPressed(KEY_R))
    {
        camera->zoom = 2.0f;
    }

    clamp(&camera->target, &stage->tile_map);

    snprintf(app.debug_menu.player_text, sizeof(app.debug_menu.player_text), "PLAYER: %.2f, %.2f", stage->player.rect.x, stage->player.rect.y);
    snprintf(app.debug_menu.camera_text, sizeof(app.debug_menu.camera_text), "CAMERA: %.2f, %.2f", camera->target.x, camera->target.y);
    snprintf(app.debug_menu.camera_zoom, sizeof(app.debug_menu.camera_zoom), "ZOOM: %.2f", camera->zoom);
}
