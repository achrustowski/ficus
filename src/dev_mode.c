#include "enums.h"
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION

#include <raygui.h>
#include "dev_mode.h"
#include "structs.h"
#include "tile_map.h"
#include "defs.h"

extern App app;
extern Game game;
static Dialog_Manager dm;

static void dev_mode_tile_map(void);
static void dev_mode_toggle(void);
static void dev_mode_dialog_create(Dialog* d, Rectangle rect, char* box_title, char* button_title, bool is_active);
static void dev_mode_dialog_operations(Dialog* d);
static void dev_mode_tileset(Tile_Set* tile_set, int width, int height, Layer_Type layer_type);
static void dev_mode_draw_tile_cursor(void);

void dev_mode_init(void);
void dev_mode_draw(Game* game);

void dev_mode_init(void)
{
    GuiLoadStyle("./styles/style_genesis.rgs");

    dm.size = 2;
    dm.dialogs = malloc(sizeof(Dialog) * dm.size);

    app.dev_mode.mouse_over = false;

    dev_mode_dialog_create(&dm.dialogs[0], (Rectangle){GetScreenWidth() - 375, 50, 160, 80}, "Tile Map WIDTH", "OK", false);
    dev_mode_dialog_create(&dm.dialogs[1], (Rectangle){GetScreenWidth() - 185, 50, 160, 80}, "Tile Map HEIGHT", "OK", false);

    sprintf(dm.dialogs[0].text, "%d", game.stage.tile_map.width);
    sprintf(dm.dialogs[1].text, "%d", game.stage.tile_map.height);
}

static void dev_mode_tileset(Tile_Set* tile_set, int width, int height, Layer_Type layer_type)
{
    app.dev_mode.mouse_over = false;
    for (int i = 0; i < tile_set->size; ++i)
    {
        int columns = tile_set->texture.width / TILE_SIZE;
        int col = i % columns;
        int row = i / columns;

        float tile_display_size = (TILE_SIZE / TILE_SCALE) * 2;

        Rectangle dest = (Rectangle)
            {GetScreenWidth() - width + (col * tile_display_size),
             GetScreenHeight() - height + (row * tile_display_size),
             tile_display_size,
             tile_display_size};

        DrawTexturePro(tile_set->texture, tile_set->tiles[i].rect, dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), dest))
        {
            DrawRectangleRec(dest, (Color){0, 0, 0, 120});
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                app.dev_mode.selected_tile_id = i;
                app.dev_mode.selected_tile_set = tile_set;
                app.dev_mode.selected_tile_layer = layer_type;
            }
            app.dev_mode.mouse_over = true;
        }
    }
}

static void dev_mode_draw_tile_cursor(void)
{
    if (app.dev_mode.selected_tile_set == NULL) return;
    Vector2 mouse = GetMousePosition();
    Rectangle source = app.dev_mode.selected_tile_set->tiles[app.dev_mode.selected_tile_id].rect;
    Rectangle dest = (Rectangle){mouse.x, mouse.y, 2 * TILE_SIZE, 2 * TILE_SIZE};
    DrawTexturePro(app.dev_mode.selected_tile_set->texture, source, dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
}

void dev_mode_logic(void)
{
    dev_mode_toggle();
}

static void dev_mode_dialog_create(Dialog* d, Rectangle rect, char* box_title, char* button_title, bool is_active)
{
    d->rect = rect;
    strcpy(d->box_title, box_title);
    strcpy(d->button_title, button_title);
    d->is_active = is_active;
}

static void dev_mode_dialog_operations(Dialog* d)
{
    GuiWindowBox(d->rect, d->box_title);
    if (GuiTextBox((Rectangle){d->rect.x + 10, d->rect.y + 35, 90, 30}, d->text, 64, d->is_active))
    {
        d->is_active = !d->is_active;
    }
}

void dev_mode_draw(Game* game)
{
    if (app.dev_mode.enabled)
    {
        GuiPanel((Rectangle){GetScreenWidth() - 400, 0, 400, GetScreenHeight()}, "DEBUG_MODE");
        for (int i = 0; i < dm.size; ++i)
        {
            dev_mode_dialog_operations(&dm.dialogs[i]);
        }
        if (GuiButton((Rectangle){dm.dialogs[0].rect.x + 115, dm.dialogs[0].rect.y + 35, 30, 30}, dm.dialogs[0].button_title))
        {
            tile_map_reassign(&game->stage, atoi(dm.dialogs[0].text), game->stage.tile_map.height);
        }
        if (GuiButton((Rectangle){dm.dialogs[1].rect.x + 115, dm.dialogs[1].rect.y + 35, 30, 30}, dm.dialogs[1].button_title))
        {
            tile_map_reassign(&game->stage, game->stage.tile_map.width, atoi(dm.dialogs[1].text));
        }
        dev_mode_tileset(&game->stage.tile_set_ground, 370, 740, LAYER_GROUND);
        dev_mode_tileset(&game->stage.tile_set_terrain_objects, 370, 370, LAYER_DECORATIONS);
        dev_mode_draw_tile_cursor();
    }

}

static void dev_mode_toggle(void)
{
    if (IsKeyPressed(KEY_P))
    app.dev_mode.enabled = !app.dev_mode.enabled;
}
