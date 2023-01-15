#pragma once
#include "global.h"

extern ALLEGRO_FONT *pirulen_36;
extern ALGIF_ANIMATION *chess_gif;
extern ALLEGRO_BITMAP *archer;
extern ALLEGRO_BITMAP *GBI; // Game Basic Interface
extern ALLEGRO_BITMAP *heart; // HP heart
extern ALGIF_ANIMATION *JI_gif; // Johnny Idle
extern ALGIF_ANIMATION *JD_gif; // Johnny dead
extern ALGIF_ANIMATION *JH_gif; // Johnny hurt
extern ALGIF_ANIMATION *JJ_gif; // Johnny jump
extern ALGIF_ANIMATION *Queen_gif; // Queen
extern ALGIF_ANIMATION *Lightening_gif; // Lightning
extern ALGIF_ANIMATION *candy_gif; // Candy
extern ALGIF_ANIMATION *warn_gif; // warn
extern ALLEGRO_FONT *score;
extern ALLEGRO_FONT *result_score;
extern ALLEGRO_BITMAP *infinite_png;
extern ALLEGRO_BITMAP *queen_text;
extern ALLEGRO_BITMAP *JD_stop;
extern ALLEGRO_BITMAP *start_button;
extern ALLEGRO_BITMAP *quit_button;
extern ALLEGRO_BITMAP *about_button;
extern ALLEGRO_BITMAP *setting_button;
extern ALLEGRO_BITMAP *remenu_button;
extern ALLEGRO_BITMAP *restart_button;
extern ALLEGRO_BITMAP *requit_button;
extern ALLEGRO_BITMAP *about;

extern float bgm_gain;
extern float se_gain;
extern ALLEGRO_SAMPLE_INSTANCE *eight_queens_bgm_spi;
extern ALLEGRO_SAMPLE_INSTANCE *easter_egg_bgm_spi;
extern ALLEGRO_SAMPLE_INSTANCE *click_se_spi;
extern ALLEGRO_SAMPLE_INSTANCE *roll_se_spi;
extern ALLEGRO_SAMPLE_INSTANCE *get_candy_spi;
extern ALLEGRO_SAMPLE_INSTANCE *lightning_spi;
extern ALLEGRO_SAMPLE_INSTANCE *dead_sound_spi;
extern ALLEGRO_SAMPLE_INSTANCE *jump_spi;



void load_resource();
void destroy_resource();

void set_bgm_gain(float);
void set_se_gain(float);
