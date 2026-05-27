#include "camera.h"
#include "stage.h"
#include <raylib.h>
#include "structs.h"

extern App app;

void camera_init(Camera2D* camera) {
    camera->target = (Vector2){0.0f, 0.0f};
    camera->offset = (Vector2){0.0f, 0.0f};
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;
}

void camera_update(Stage* stage, Camera2D* camera) {
    // Update the target to follow the player
    camera->target.x = stage->player.position.x;
    camera->target.y = stage->player.position.y;

    // Calculate the offset based on the screen dimensions and camera zoom
    camera->offset.x = GetScreenWidth() / 2.0f - camera->target.x * camera->zoom;
    camera->offset.y = GetScreenHeight() / 2.0f - camera->target.y * camera->zoom;

    // Ensure the offset does not go out of bounds
    if (camera->offset.x < 0) camera->offset.x = 0;
    if (camera->offset.x > stage->tile_map.width * tile_width * camera->zoom - GetScreenWidth()) camera->offset.x = stage->tile_map.width * tile_width * camera->zoom - GetScreenWidth();
    if (camera->offset.y < 0) camera->offset.y = 0;
    if (camera->offset.y > stage->tile_map.height * tile_height * camera->zoom - GetScreenHeight()) camera->offset.y = stage->tile_map.height * tile_height * camera->zoom - GetScreenHeight();

    // Update the camera position
    camera->position.x = camera->target.x + camera->offset.x;
    camera->position.y = camera->target.y + camera->offset.y;

    // Apply the camera transformation
    BeginMode2D(camera);
}
