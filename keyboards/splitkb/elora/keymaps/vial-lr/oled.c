#include <string.h>
#include <stdio.h>
#include "layers.h"

#define LAYER_DISPLAY_FIRST_ROW = 3; // 0 indexed

void print_layer_status(void) {
    static const char OLED_LAYER_MAP[] PROGMEM = "NMSFA";

    char layerStatus[(TMP_LAYER_COUNT * 2) + 1];
    for(uint8_t layerOffset = 0; layerOffset < TMP_LAYER_COUNT; layerOffset += 1) {
        uint8_t layer = layerOffset + FIRST_TMP_LAYER;
        uint8_t start = layerOffset * 2;
        sprintf(layerStatus + start, PSTR("%c "), IS_LAYER_ON(layer) ? *(OLED_LAYER_MAP + layerOffset) : *(PSTR(" ")));
    }

    oled_write(layerStatus, false);
}

/*
    Just print some numbers out to indicate max width
*/
void print_sizing(void) {
    oled_write_ln_P("0123456789abcdef", false);
}

void next_line(void) {
    oled_write_ln_P(PSTR(""), false);
}

void print_led_usb_state(void) {
    // Keyboard LED Status
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR(" S"), led_usb_state.scroll_lock);
    oled_write_P(PSTR(" C"), led_usb_state.caps_lock);
    oled_write_P(PSTR(" N"), led_usb_state.num_lock);
}

bool lr_oled_task_master(void) {
    oled_write_P(PSTR("Lyrael\n\n"), false);
    oled_write_P(IS_LAYER_ON_STATE(default_layer_state, _QWGAM) ? PSTR("Gam") : PSTR("Typ"), false);

    print_led_usb_state();
    next_line();

    print_layer_status();
    next_line();

//    oled_set_cursor(0, oled_max_lines()-3);
//    print_sizing();

    return false;
}

bool lr_oled_task_slave(void) {
    // just use the keyboard code for now.
    return true;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        return lr_oled_task_master();
    } else {
        return lr_oled_task_slave();
    }
}
