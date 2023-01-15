#include "about.h"
#include "resource.h"

void about_init() {}

void about_destroy() {}

int about_process(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_KEY_DOWN &&
        event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
        return MSG_BACK_TO_MENU;
    }
    return MSG_NOPE;
}

void about_draw() {
    al_draw_scaled_bitmap(about, 0, 0, 1563, 1980, 0, 0, 760, 950, 0);
}
