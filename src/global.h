#pragma once
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../algif5/src/algif.h"

enum {
    MSG_TERMINATE,
    MSG_NOPE,
    MSG_GAME_START,
    MSG_GAME_OVER,
    MSG_GAME_RESTART,
    MSG_BACK_TO_MENU,
    MSG_CHANGE_SETTING,
    MSG_ABOUT
};

extern const int WIDTH;
extern const int HEIGHT;
extern const double FPS;
extern int msg;

extern ALLEGRO_EVENT_QUEUE *scene_queue;
extern ALLEGRO_DISPLAY *scene_display;
extern ALLEGRO_TIMER *scene_timer;

extern int key_left;
extern int key_right;
extern int key_up;
extern int key_down;

extern bool easter_egg_mode;

extern int board[8][8];
extern int number;
