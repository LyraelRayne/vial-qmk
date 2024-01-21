#include <string.h>
#include <stdio.h>
#include "layers.h"

void oled_white_space(void) {
  oled_write_P(PSTR(" "), false);
}

void print_layer_status(void) {
    static const char OLED_LAYER_MAP[][4] PROGMEM = {
        "NAV",
        "MOU",
        "SYM",
        "FUN",
        "ADJ",
        "_X_"
    };

    for(uint8_t layerOffset = 0; layerOffset < TMP_LAYER_COUNT; layerOffset += 1) {
        uint8_t layer = layerOffset + FIRST_TMP_LAYER;
        oled_write(OLED_LAYER_MAP[layerOffset], IS_LAYER_ON(layer));
        if((layerOffset + 1) % 2 == 0) {
            oled_advance_page(true);
        } else {
            oled_white_space();
        }
    }
}

void print_led_usb_state(void) {
    // Keyboard LED Status
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR("SC"), led_usb_state.scroll_lock);
    oled_write_P(PSTR("CA"), led_usb_state.caps_lock);
    oled_write_P(PSTR("NU"), !led_usb_state.num_lock);
}

// Adapted from keyboards/splitkb/kyria/keymaps/john-ezra/oled.c
void render_mod_state(uint8_t modifiers) {
  oled_write_P(PSTR("SHF"), (modifiers & MOD_MASK_SHIFT));
  oled_white_space();
  oled_write_P(PSTR("CTL"), (modifiers & MOD_MASK_CTRL));
  oled_advance_page(false);
  oled_write_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
  oled_white_space();
  oled_write_P(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
}

bool lr_oled_task_master(void) {
    oled_write_ln_P(PSTR("Lyrael"), false);
    oled_advance_page(true);

    oled_write_P(IS_LAYER_ON_STATE(default_layer_state, _QWGAM) ? PSTR("Gam") : PSTR("Typ"), false);
    oled_white_space();
    print_led_usb_state();

    oled_advance_page(true);
    print_layer_status();
    oled_advance_page(true);

    oled_set_cursor(0, oled_max_lines() - 6);
    render_mod_state(get_mods()|get_oneshot_mods());
//    oled_write_ln_P(PSTR("0123456789abcdef"), false);
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
