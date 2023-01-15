#include "menu.h"
#include "resource.h"
int button_index = 0;
struct {
    float old_angle;
    float base_angle;
    float angle;
    bool pressed;
} easter_egg;

void menu_init() {
    easter_egg.angle = easter_egg_mode ? (ALLEGRO_PI / 2) : 0.0f;
    easter_egg.pressed = false;
}

void menu_destroy() {}

int menu_process(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if(event.keyboard.keycode == ALLEGRO_KEY_DOWN){
            if(button_index <= 2){
                button_index++;
            }
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_UP){
            if(button_index>0){
                button_index--;
            }
        }
        if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            al_play_sample_instance(click_se_spi);
            if (button_index == 0) {
                return MSG_GAME_START;
            } else if (button_index == 1) {
                return MSG_CHANGE_SETTING;
            } else if (button_index == 2) {
                return MSG_TERMINATE;
            } else {
                return MSG_ABOUT;
            }
        }
    }

    // easter egg
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1
        && ((event.mouse.x - 210)*(event.mouse.x - 210)+(event.mouse.y -200)*(event.mouse.y - 200)) < 2500) {
        easter_egg.pressed = true;
        easter_egg.old_angle = easter_egg.angle;
        easter_egg.base_angle = atan2f(event.mouse.x - 210, event.mouse.y - 200);
    } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 1) {
        easter_egg.pressed = false;

        const float d_theta = 0.1f;
        if (fabs(cos(easter_egg.angle)) < d_theta) {
            easter_egg_mode = true;
            al_stop_sample_instance(eight_queens_bgm_spi);
            al_play_sample_instance(easter_egg_bgm_spi);
        } else {
            easter_egg_mode = false;
            al_stop_sample_instance(easter_egg_bgm_spi);
            al_play_sample_instance(eight_queens_bgm_spi);
        }
    }

    if (easter_egg.pressed) {
        ALLEGRO_MOUSE_STATE mouse_state;
        al_get_mouse_state(&mouse_state);
        int dx = mouse_state.x - 210;
        int dy = mouse_state.y - 200;
        easter_egg.angle = easter_egg.old_angle + (atan2f(dx, dy) - easter_egg.base_angle);
    }

    return MSG_NOPE;
}

void menu_draw() {
// void menu_draw(ALLEGRO_EVENT event) {
    // al_clear_to_color(al_map_rgb(200, 177, 177));
    // al_draw_text(pirulen_36, al_map_rgb(0, 0, 0), WIDTH/2, 450, ALLEGRO_ALIGN_CENTER, "This is menu");
    if(button_index == 0){
        al_draw_scaled_bitmap(start_button, 0, 0, 1563, 1980, 0, 0, 760, 950, 0);
    }
    else if(button_index == 1){
        al_draw_scaled_bitmap(setting_button, 0, 0, 1563, 1980, 0, 0, 760, 950, 0);
    }
    else if(button_index == 2){
        al_draw_scaled_bitmap(quit_button, 0, 0, 1563, 1980, 0, 0, 760, 950, 0);
    }
    else if(button_index == 3){
        al_draw_scaled_bitmap(about_button, 0, 0, 1563, 1980, 0, 0, 760, 950, 0);
    }
    al_draw_scaled_rotated_bitmap(infinite_png, 62.5f, 62.5f, 220.0f, 210.0f,0.5,0.5, -easter_egg.angle, 0);
    al_draw_scaled_bitmap(queen_text, 0, 0,730,730,240,30,385,385, 0);
}
