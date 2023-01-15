#include "setting.h"
#include "resource.h"

int selected;
bool key_left_pressed;
bool key_right_pressed;

float clamp(float v, float l, float u) {
    if (v < l) {
        return l;
    } else if (v > u) {
        return u;
    } else {
        return v;
    }
}

void setting_init() {
    selected = 0;
    key_left_pressed = false;
    key_right_pressed = false;
    
}

void setting_destroy() {}

int setting_process(ALLEGRO_EVENT event) {

    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            al_play_sample_instance(click_se_spi);
            return MSG_BACK_TO_MENU;
        } else if (event.keyboard.keycode == key_down && selected < 1) {
            ++selected;
        } else if (event.keyboard.keycode == key_up && selected > 0) {
            --selected;
        } else if (event.keyboard.keycode == key_left) {
            key_left_pressed = true;
        } else if (event.keyboard.keycode == key_right) {
            key_right_pressed = true;
        }
    } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
        if (event.keyboard.keycode == key_left) {
            key_left_pressed = false;
        } else if (event.keyboard.keycode == key_right) {
            key_right_pressed = false;
        }
    }

    if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == scene_timer) {
        const float d_gain = 0.005f;
        if (selected == 0) {
            if (key_left_pressed || key_right_pressed) {
                float new_gain = key_left_pressed ? (bgm_gain - d_gain) : (bgm_gain + d_gain); 
                new_gain = clamp(new_gain, 0.0f, 1.0f);
                if (new_gain != bgm_gain) {
                    set_bgm_gain(new_gain);
                }
            }
        } else {
            if (key_left_pressed || key_right_pressed) {
                float new_gain = key_left_pressed ? (se_gain - d_gain) : (se_gain + d_gain); 
                new_gain = clamp(new_gain, 0.0f, 1.0f);
                if (new_gain != se_gain) {
                    set_se_gain(new_gain);
                }
            }
        }
    }

    return MSG_NOPE;
}

void setting_draw() {
    al_clear_to_color(al_map_rgb(200, 200, 255));

    const float selector_offset_x = 25.0f;
    const float padding = 50.0f;
    const float bgm_h = 150.0f;
    const float se_h = 450.0f;
    const float scalar_offset_y = 70.0f;
    const float bar_offset_y = 150.0f;
    const ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
    const float circle_r = 15.0f;
    const float bar_padding = padding + circle_r;
    const float bar_thickness = 5.0f;
    const ALLEGRO_COLOR circle_color = al_map_rgb(255, 255, 255);

    // bgm
    al_draw_text(pirulen_36, black, padding, bgm_h, ALLEGRO_ALIGN_LEFT, "BGM");
    al_draw_text(pirulen_36, black, padding, bgm_h + scalar_offset_y, ALLEGRO_ALIGN_LEFT, "0");
    al_draw_text(pirulen_36, black, WIDTH - padding, bgm_h + scalar_offset_y, ALLEGRO_ALIGN_RIGHT, "100");
    al_draw_line(bar_padding, bgm_h + bar_offset_y, WIDTH - bar_padding, bgm_h + bar_offset_y, black, bar_thickness); 
    al_draw_filled_circle(bar_padding + (WIDTH - bar_padding * 2) * bgm_gain, bgm_h + bar_offset_y, circle_r + 4.0f, black);
    al_draw_filled_circle(bar_padding + (WIDTH - bar_padding * 2) * bgm_gain, bgm_h + bar_offset_y, circle_r, circle_color);

    // se
    al_draw_text(pirulen_36, black, padding, se_h, ALLEGRO_ALIGN_LEFT, "SE");
    al_draw_text(pirulen_36, black, padding, se_h + scalar_offset_y, ALLEGRO_ALIGN_LEFT, "0");
    al_draw_text(pirulen_36, black, WIDTH - padding, se_h + scalar_offset_y, ALLEGRO_ALIGN_RIGHT, "100");
    al_draw_line(bar_padding, se_h + bar_offset_y, WIDTH - bar_padding, se_h + bar_offset_y, black, bar_thickness); 
    al_draw_filled_circle(bar_padding + (WIDTH - bar_padding * 2) * se_gain, se_h + bar_offset_y, circle_r + 4.0f, black);
    al_draw_filled_circle(bar_padding + (WIDTH - bar_padding * 2) * se_gain, se_h + bar_offset_y, circle_r, circle_color);

    // selector
    al_draw_text(pirulen_36, black, selector_offset_x, (selected == 0) ? bgm_h : se_h, ALLEGRO_ALIGN_LEFT, ">");
}
