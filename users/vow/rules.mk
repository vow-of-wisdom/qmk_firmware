# rules.mk


SRC += french_oss_sendstring.c
SRC += vow.c


# Features
COMBO_ENABLE          = yes
EXTRAKEY_ENABLE       = yes
KEY_OVERRIDE_ENABLE   = yes
REPEAT_KEY_ENABLE     = yes
RGBLIGHT_ENABLE       = yes

# Build
LTO_ENABLE            = yes

# Debug
CONSOLE_ENABLE        = no
KEYCODE_STRING_ENABLE = yes
