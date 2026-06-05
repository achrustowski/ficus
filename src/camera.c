#include <raylib.h>
#include <string.h>
#include "camera.h"
#include <math.h>
#include <stdio.h>
#include "defs.h"

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
    float map_w = stage->tile_map.width  * TILE_SIZE;
    float map_h = stage->tile_map.height * TILE_SIZE;

    float min_zoom = fmaxf((camera->offset.x * 2.0f) / map_w,
                           (camera->offset.y * 2.0f) / map_h);

    camera->zoom = expf(logf(camera->zoom) + (float)(GetMouseWheelMove() * 0.1f));
    camera->zoom = CLAMP(camera->zoom, min_zoom, 10.0f);

    if (IsKeyPressed(KEY_R))
        camera->zoom = 2.0f;

    float half_w = camera->offset.x / camera->zoom;
    float half_h = camera->offset.y / camera->zoom;
    float cx = stage->player.rect.x + stage->player.rect.width  / 2.0f;
    float cy = stage->player.rect.y + stage->player.rect.height / 2.0f;

    camera->target.x = CLAMP((int)cx, half_w, map_w - half_w);
    camera->target.y = CLAMP((int)cy, half_h, map_h - half_h);

    snprintf(app.debug_menu.player_text, sizeof(app.debug_menu.player_text), "PLAYER: %.2f, %.2f", stage->player.rect.x, stage->player.rect.y);
    snprintf(app.debug_menu.camera_text, sizeof(app.debug_menu.camera_text), "CAMERA: %.2f, %.2f", camera->target.x, camera->target.y);
    snprintf(app.debug_menu.camera_zoom, sizeof(app.debug_menu.camera_zoom), "ZOOM: %.2f", camera->zoom);
}
