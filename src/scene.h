#pragma once
#include "global.h"

enum {
    SCENE_MENU,
    SCENE_GAME,
    SCENE_RESULT,
    SCENE_SETTING,
    SCENE_ABOUT
};

void scene_init();
void scene_begin();
void scene_destroy();
int scene_run();
int scene_process(ALLEGRO_EVENT);
void scene_draw();
// extern int msg;
