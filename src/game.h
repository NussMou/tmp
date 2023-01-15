#pragma once
#include "global.h"

void game_init();
void game_destroy();
int game_process(ALLEGRO_EVENT);
void game_draw();
void heart_draw();
void score_draw();
void queens_process(int n);
void candy_process();