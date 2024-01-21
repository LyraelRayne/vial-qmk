#pragma once
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _QWGAM,
    _NAV,
    _MOUSE,
    _SYM,
    _FUNCTION,
    _ADJUST,
    _X,
};

static const uint8_t LAST_TMP_LAYER PROGMEM = _X;
static const uint8_t FIRST_TMP_LAYER PROGMEM = _NAV;
static const uint8_t TMP_LAYER_COUNT PROGMEM = LAST_TMP_LAYER - FIRST_TMP_LAYER + 1;
