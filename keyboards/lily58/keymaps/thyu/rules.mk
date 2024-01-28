VIA_ENABLE = yes
WPM_ENABLE = yes
LTO_ENABLE = yes
OLED_ENABLE = yes
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
		./lib/layer_state_reader.c \
		./lib/logo_reader.c \
		./lib/keylogger.c \

