#include "resource.h"

ALLEGRO_FONT *pirulen_36;
ALGIF_ANIMATION *chess_gif;
ALLEGRO_BITMAP *archer;
ALLEGRO_BITMAP *GBI; // Game Basic Interface
ALLEGRO_BITMAP *heart;
ALGIF_ANIMATION *JI_gif ;
ALGIF_ANIMATION *JD_gif;
ALGIF_ANIMATION *JH_gif;
ALGIF_ANIMATION *JJ_gif;
ALGIF_ANIMATION *Queen_gif;
ALGIF_ANIMATION *Lightening_gif;
ALGIF_ANIMATION *candy_gif;
ALGIF_ANIMATION *warn_gif;
ALLEGRO_FONT *score;
ALLEGRO_FONT *result_score;
ALLEGRO_BITMAP *start_button;
ALLEGRO_BITMAP *quit_button;
ALLEGRO_BITMAP *about_button;
ALLEGRO_BITMAP *setting_button;
ALLEGRO_BITMAP *remenu_button;
ALLEGRO_BITMAP *restart_button;
ALLEGRO_BITMAP *requit_button;
ALLEGRO_BITMAP *about;

ALLEGRO_BITMAP *infinite_png;
ALLEGRO_BITMAP *queen_text;
ALLEGRO_BITMAP *JD_stop;

float bgm_gain = 1.0f;
float se_gain = 1.0f;
ALLEGRO_SAMPLE *eight_queens_bgm_sp;
ALLEGRO_SAMPLE_INSTANCE *eight_queens_bgm_spi;
ALLEGRO_SAMPLE *easter_egg_bgm_sp;
ALLEGRO_SAMPLE_INSTANCE *easter_egg_bgm_spi;
ALLEGRO_SAMPLE *click_se_sp;
ALLEGRO_SAMPLE_INSTANCE *click_se_spi;
ALLEGRO_SAMPLE *roll_se_sp;
ALLEGRO_SAMPLE_INSTANCE *roll_se_spi;
ALLEGRO_SAMPLE_INSTANCE *get_candy_spi;
ALLEGRO_SAMPLE *get_candy_sp;
ALLEGRO_SAMPLE_INSTANCE *lightning_spi;
ALLEGRO_SAMPLE *lightning_sp;
ALLEGRO_SAMPLE_INSTANCE *dead_sound_spi;
ALLEGRO_SAMPLE *dead_sound_sp;
ALLEGRO_SAMPLE_INSTANCE *jump_spi;
ALLEGRO_SAMPLE *jump_sp;

void load_sound(const char *filename, ALLEGRO_SAMPLE **sp, ALLEGRO_SAMPLE_INSTANCE **spi, ALLEGRO_PLAYMODE playmode) {
    *sp = al_load_sample(filename);
    *spi = al_create_sample_instance(*sp);
    al_set_sample_instance_playmode(*spi, playmode);
    al_attach_sample_instance_to_mixer(*spi, al_get_default_mixer());
}

void destroy_sound(ALLEGRO_SAMPLE *sp, ALLEGRO_SAMPLE_INSTANCE *spi) {
    al_destroy_sample_instance(spi);
    al_destroy_sample(sp);
}

void load_resource() {
    pirulen_36 = al_load_ttf_font("../res/font/pirulen.ttf", 36, 0);
    chess_gif = algif_load_animation("../res/image/chess.gif");
    archer = al_load_bitmap("../res/image/archer.png");
    GBI = al_load_bitmap("../res/image/game_basic_interface.png"); //Game basic Interface
    JI_gif = algif_load_animation("../res/image/Johnny_idle.gif"); //Johnny Idle
    JD_gif = algif_load_animation("../res/image/Johnny_dead.gif"); //Johnny dead
    JH_gif = algif_load_animation("../res/image/Johnny_hurt.gif"); //Johnny hurt
    JJ_gif = algif_load_animation("../res/image/Johnny_jump.gif"); //Johnny jump
    Queen_gif = algif_load_animation("../res/image/queen2.gif"); // queen idle
    Lightening_gif = algif_load_animation("../res/image/Lightening.gif"); // Lightening
    candy_gif = algif_load_animation("../res/image/candy.gif");
    warn_gif = algif_load_animation("../res/image/warning.gif");
    heart = al_load_bitmap("../res/image/heart.png");
    score = al_load_ttf_font("../res/font/pirulen.ttf", 40, 0);
    result_score = al_load_ttf_font("../res/font/pirulen.ttf", 80, 0);
    infinite_png = al_load_bitmap("../res/image/8.png");
    queen_text = al_load_bitmap("../res/image/Queens_text.png");
    JD_stop = al_load_bitmap("../res/image/JD_stop.png");
    start_button = al_load_bitmap("../res/image/start_button.png");
    quit_button = al_load_bitmap("../res/image/quit_button.png");
    about_button = al_load_bitmap("../res/image/about_button.png");
    setting_button = al_load_bitmap("../res/image/setting_button.png");
    restart_button = al_load_bitmap("../res/image/restart_button.png");
    requit_button = al_load_bitmap("../res/image/requit_button.png");
    remenu_button = al_load_bitmap("../res/image/remenu_button.png");
    about = al_load_bitmap("../res/image/about.png");

    load_sound("../res/sound/8_queens_bgm.wav", &eight_queens_bgm_sp, &eight_queens_bgm_spi, ALLEGRO_PLAYMODE_LOOP);
    load_sound("../res/sound/easter_egg_bgm.wav", &easter_egg_bgm_sp, &easter_egg_bgm_spi, ALLEGRO_PLAYMODE_LOOP);
    load_sound("../res/sound/click_se.wav", &click_se_sp, &click_se_spi, ALLEGRO_PLAYMODE_ONCE);
    load_sound("../res/sound/roll_se.wav", &roll_se_sp, &roll_se_spi, ALLEGRO_PLAYMODE_ONCE);
    load_sound("../res/sound/get_candy.wav", &get_candy_sp, &get_candy_spi, ALLEGRO_PLAYMODE_ONCE);
    load_sound("../res/sound/lightning.wav", &lightning_sp, &lightning_spi, ALLEGRO_PLAYMODE_ONCE);
    load_sound("../res/sound/Johnny_dead.wav", &dead_sound_sp, &dead_sound_spi, ALLEGRO_PLAYMODE_ONCE);
    load_sound("../res/sound/Johnny_jump.wav", &jump_sp, &jump_spi, ALLEGRO_PLAYMODE_ONCE);
}
void destroy_resource() {
    al_destroy_font(pirulen_36);
    algif_destroy_animation(chess_gif);
    al_destroy_bitmap(archer);

    al_destroy_bitmap(infinite_png);
    al_destroy_bitmap(queen_text);

    destroy_sound(eight_queens_bgm_sp, eight_queens_bgm_spi);
    destroy_sound(easter_egg_bgm_sp, easter_egg_bgm_spi);
    destroy_sound(click_se_sp, click_se_spi);
    destroy_sound(roll_se_sp, roll_se_spi);
}

void set_bgm_gain(float gain) {
    bgm_gain = gain;
    al_set_sample_instance_gain(eight_queens_bgm_spi, gain);
    al_set_sample_instance_gain(easter_egg_bgm_spi, gain);
}

void set_se_gain(float gain) {
    se_gain = gain;
    al_set_sample_instance_gain(click_se_spi, gain);
    al_set_sample_instance_gain(roll_se_spi, gain);
}
