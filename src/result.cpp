#include "result.h"
#include "resource.h"
#include "game.h"

int re_button_index = 0;
void result_init() {}

void result_destroy() {}

int result_process(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if(event.keyboard.keycode == ALLEGRO_KEY_DOWN){
            if(re_button_index <= 1){
                re_button_index++;
            }
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_UP){
            if(re_button_index>0){
                re_button_index--;
            }
        }
        if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && re_button_index == 0) {
            al_play_sample_instance(click_se_spi);
            al_stop_sample_instance(dead_sound_spi);
            return MSG_GAME_RESTART;
        } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && re_button_index == 1) {
            al_play_sample_instance(click_se_spi);
            al_stop_sample_instance(dead_sound_spi);
            return MSG_TERMINATE;
        }else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && re_button_index == 2) {
            al_play_sample_instance(click_se_spi);
            al_stop_sample_instance(dead_sound_spi);
            return MSG_BACK_TO_MENU;
        }

    }

    return MSG_NOPE;
}

void result_draw() {
    // al_clear_to_color(al_map_rgb(255, 255, 200));
    // al_draw_text(pirulen_36, al_map_rgb(0, 0, 0), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTER, "This is result");
    if(re_button_index == 0){
        al_draw_scaled_bitmap(restart_button, 0, 0, 1563, 1980, 0, 0, 760, 950, 0);
    }
    else if(re_button_index == 1){
        al_draw_scaled_bitmap(requit_button, 0, 0, 1563, 1980, 0, 0, 760, 950, 0);
    }
    else if(re_button_index == 2){
        al_draw_scaled_bitmap(remenu_button, 0, 0, 1563, 1980, 0, 0, 760, 950, 0);
    }
    al_draw_textf(result_score, al_map_rgb(255,255,255), 350,250, ALLEGRO_ALIGN_CENTER,  "%3d",number);
}
