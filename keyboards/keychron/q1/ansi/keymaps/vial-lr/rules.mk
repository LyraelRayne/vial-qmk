# Q1 Defaults + VIAL
VIA_ENABLE = yes
VIAL_ENABLE = yes

# RGB Control :D
VIALRGB_ENABLE = yes # 856 bytes
KEY_LOCK_ENABLE = yes
CAPS_WORD_ENABLE = yes

TAP_DANCE_ENABLE = no
QMK_SETTINGS = no # 2418 bytes.
COMBO_ENABLE = yes # 2666 bytes
EXTRAKEY_ENABLE = yes # 366 bytes... yikes
MOUSEKEY_ENABLE = yes # 1882 bytes
KEY_OVERRIDE_ENABLE = no

CONSOLE_ENABLE = no

###
#VPATH += keyboards/keychron/common
#SRC += keychron_common.c

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += rgb_matrix_user.c
endif
