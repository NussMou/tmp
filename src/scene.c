#include "scene.h"
#include "menu.h"
#include "game.h"
#include "result.h"
#include "resource.h"
#include "setting.h"
#include "about.h"

int scene_state;

void scene_init() {
    al_init();
    // keyboard
    al_install_keyboard();
    // mouse
    al_install_mouse();
    // audio
    al_install_audio();
    al_init_acodec_addon();
    al_restore_default_mixer();
    // primitives
    al_init_primitives_addon();
    // image & text
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    scene_queue = al_create_event_queue();
    scene_display = al_create_display(WIDTH, HEIGHT);
    scene_timer = al_create_timer(1.0 / FPS);

    al_set_window_title(scene_display, "8_queens");
    al_set_window_position(scene_display, 500, 0);

    al_register_event_source(scene_queue, al_get_display_event_source(scene_display));
    al_register_event_source(scene_queue, al_get_timer_event_source(scene_timer));
    al_register_event_source(scene_queue, al_get_keyboard_event_source());
    al_register_event_source(scene_queue, al_get_mouse_event_source());

    load_resource();
    srand(time(NULL));
}

void scene_begin() {
    scene_state = SCENE_MENU;
    menu_init();
    al_start_timer(scene_timer);
    al_play_sample_instance(eight_queens_bgm_spi);
}

void scene_destroy() {
    al_destroy_event_queue(scene_queue);
    al_destroy_display(scene_display);
    al_destroy_timer(scene_timer);
    destroy_resource();
}

int scene_run() {
    ALLEGRO_EVENT event;
    al_wait_for_event(scene_queue, &event);
    // if the window was closed, then terminate the program
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE && event.display.source == scene_display) {
        return MSG_TERMINATE;
    }

    if (scene_process(event) == MSG_TERMINATE) {
        return MSG_TERMINATE;
    }

    if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == scene_timer) {
        scene_draw();
    }
    return MSG_NOPE;

}

int scene_process(ALLEGRO_EVENT event) {
    int msg;
    if (scene_state == SCENE_MENU) {
        msg = menu_process(event);
        // printf("final\n");
        if (msg == MSG_GAME_START) {
            menu_destroy();
            scene_state = SCENE_GAME;
            game_init();
        } else if (msg == MSG_CHANGE_SETTING) {
            menu_destroy();
            scene_state = SCENE_SETTING;
            setting_init();
        } else if (msg == MSG_TERMINATE) {
            return MSG_TERMINATE;
        } else if (msg == MSG_ABOUT) {
            menu_destroy();
            scene_state = SCENE_ABOUT;
            about_init();
        }
    } else if (scene_state == SCENE_GAME) {
        msg = game_process(event);
        if (msg == MSG_GAME_OVER) {
            game_destroy();
            scene_state = SCENE_RESULT;
            result_init();
        }
    } else if (scene_state == SCENE_RESULT) {
        msg = result_process(event);
        if (msg == MSG_GAME_RESTART) {
            result_destroy();
            scene_state = SCENE_GAME;
            game_init();
        } else if (msg == MSG_BACK_TO_MENU) {
            result_destroy();
            scene_state = SCENE_MENU;
            menu_init();
        } else if (msg == MSG_TERMINATE) {
            return MSG_TERMINATE;
        }
    } else if (scene_state == SCENE_SETTING) {
        msg = setting_process(event);
        if (msg == MSG_BACK_TO_MENU) {
            setting_destroy();
            scene_state = SCENE_MENU;
            menu_init();
        }
    } else if (scene_state == SCENE_ABOUT) {
        msg = about_process(event);
        if (msg == MSG_BACK_TO_MENU) {
            about_destroy();
            scene_state = SCENE_MENU;
            menu_init();
        }
    }
    return MSG_NOPE;
}

void scene_draw() {
    if (scene_state == SCENE_MENU) {
        menu_draw();
    } else if (scene_state == SCENE_GAME) {
        game_draw();
    } else if (scene_state == SCENE_RESULT) {
        result_draw();
    } else if (scene_state == SCENE_SETTING) {
        setting_draw();
    } else if (scene_state == SCENE_ABOUT) {
        about_draw();
    }
    al_flip_display();
}
