#include <raylib.h>

#define RAYGUI_IMPLEMENTATION

#include <raygui.h>
#include "dev_mode.h"
#include "structs.h"
#include "tile_map.h"

extern App app;
extern Game game;
static Dialog_Manager dm;

static void dev_mode_tile_map(void);
static void dev_mode_toggle(void);
static void dialog_create(Dialog* d, Rectangle rect, char* box_title, char* button_title, bool is_active);
static void dialog_operations(Dialog* d);

void dev_mode_init(void);
void dev_mode_draw(void);

void dev_mode_init(void)
{
    GuiLoadStyle("./styles/style_genesis.rgs");

    dm.size = 2;
    dm.dialogs = malloc(sizeof(Dialog) * dm.size);

    dialog_create(&dm.dialogs[0], (Rectangle){GetScreenWidth() - 375, 70, 160, 80}, "Tile Map WIDTH", "OK", false);
    dialog_create(&dm.dialogs[1], (Rectangle){GetScreenWidth() - 185, 70, 160, 80}, "Tile Map HEIGHT", "OK", false);
}

void dev_mode_logic(void)
{
    dev_mode_toggle();
}

static void dialog_create(Dialog* d, Rectangle rect, char* box_title, char* button_title, bool is_active)
{
    d->rect = rect;
    strcpy(d->box_title, box_title);
    strcpy(d->button_title, button_title);
    d->is_active = is_active;
}

static void dialog_operations(Dialog* d)
{
    GuiWindowBox(d->rect, d->box_title);
    if (GuiTextBox((Rectangle){d->rect.x + 10, d->rect.y + 35, 90, 30}, d->text, 64, d->is_active))
    {
        d->is_active = !d->is_active;
    }
}

void dev_mode_draw(void)
{
    if (app.dev_mode_enabled)
    {
        GuiPanel((Rectangle){GetScreenWidth() - 400, 0, 400, GetScreenHeight()}, "DEBUG_MODE");
        for (int i = 0; i < dm.size; ++i)
        {
            dialog_operations(&dm.dialogs[i]);
        }
        if (GuiButton((Rectangle){dm.dialogs[0].rect.x + 115, dm.dialogs[0].rect.y + 35, 30, 30}, dm.dialogs[0].button_title))
        {
            tile_map_reassign(&game.stage, atoi(dm.dialogs[0].text), game.stage.tile_map.height);
        }
        if (GuiButton((Rectangle){dm.dialogs[1].rect.x + 115, dm.dialogs[1].rect.y + 35, 30, 30}, dm.dialogs[1].button_title))
        {
            tile_map_reassign(&game.stage, game.stage.tile_map.height, atoi(dm.dialogs[1].text));
        }
    }
}

static void dev_mode_toggle(void)
{
    if (IsKeyPressed(KEY_P))
    {
        if (app.dev_mode_enabled) app.dev_mode_enabled = false;
        else app.dev_mode_enabled = true;
    }
}
