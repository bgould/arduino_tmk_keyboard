TOP_DIR=`pwd`

COMMON_DIR = $(TOP_DIR)/../tmk_keyboard/common
COMMON_HEADERS =	report.h \
				keycode.h \
				matrix.h \
				util.h \
				debug.h \
				debug_config.h \
				keyboard.h \
				keymap.h \
				host.h \
				led.h \
				command.h \
				sendchar.h \
				bootmagic.h \
				eeconfig.h \
				mousekey.h \
				backlight.h \
				host_driver.h \
				action.h \
				action_code.h \
				action_layer.h \
				action_macro.h \
				action_tapping.h \
				action_util.h \
				nodebug.h \
				suspend.h \
				timer.h \
				

COMMON_SOURCES =  keyboard.c \
				action.c \
				action_layer.c \
				action_macro.c \
				action_tapping.c \
				action_util.c \
				host.c \
				keymap.c \
				util.c \
				suspend.c \
				timer.c \

COMMON_FILES=$(COMMON_HEADERS) $(COMMON_SOURCES)
				
#		backlight.h \
#		bootloader.c \
#		bootloader.h \
#		bootmagic.h \
#		command.h \
#		debug.h \
#		debug_config.h \
#		eeconfig.h \
#		led.h \
#		keyboard.h \
#		keycode.h \

#		keymap.h \
#		matrix.h \
#		mousekey.c \
#		mousekey.h \

#		print.c \
#		print.h \
#		report.h \
#		sendchar.h \
#		suspend.c \
#		suspend.h \
#		timer.c \
#		timer.h \
#		util.h 

PS2_DIR=$(TOP_DIR)/../tmk_keyboard/protocol
PS2_FILES =		ps2.h \
				ps2.c
#		serial.h \
#		ps2.c \
#		ps2.h 

TMK_FILES=$(COMMON_FILES) $(PS2_FILES)

TARGETS= 	ps2.h ps2_codeset2_matrix.h ps2_codeset3_matrix.h \
			action.h action_layer.h action_macro.h action_tapping.h action_util.h \
			host.h keyboard.h keymap.h util.h \
			suspend.h timer.h \
			

all: copy-tmk-files tmk_keyboard.c $(TARGETS)

tmk_keyboard.h: tmk_keyboard.h.in copy-tmk-files
	cp $< $@ 

copy-tmk-files:
	cp $(patsubst %, $(COMMON_DIR)/% ,$(COMMON_FILES)) $(patsubst %, $(PS2_DIR)/%,$(PS2_FILES)) $(TOP_DIR)

ps2_codeset2_matrix.h:
	cp $(TOP_DIR)/../tmk_keyboard/converter/ps2_usb/matrix.c $(TOP_DIR)/ps2_codeset2_matrix.h

ps2_codeset3_matrix.h:
	cp $(TOP_DIR)/../tmk_keyboard/converter/terminal_usb/matrix.c $(TOP_DIR)/ps2_codeset3_matrix.h

tmk_keyboard.c: copy-tmk-files
	touch $(TOP_DIR)/tmk_keyboard.c;
	rm $(TOP_DIR)/tmk_keyboard.c;
	@echo '#include "tmk_keyboard.h"' >> $(TOP_DIR)/tmk_keyboard.c;
	@echo '' >> $(TOP_DIR)/tmk_keyboard.c;

%.h: tmk_keyboard.c
	@echo "" >> $(TOP_DIR)/tmk_keyboard.c; 
	@echo "#ifndef TMK_SOURCE_$*_H__" >> $(TOP_DIR)/tmk_keyboard.c; 
	@echo "#define TMK_SOURCE_$*_H__ 1" >> $(TOP_DIR)/tmk_keyboard.c; 
	cat $(TOP_DIR)/$*.c >> $(TOP_DIR)/tmk_keyboard.c;
	@echo "" >> $(TOP_DIR)/tmk_keyboard.c; 
	@echo "#endif" >> $(TOP_DIR)/tmk_keyboard.c;
	@rm $(TOP_DIR)/$*.c;

clean:
	rm tmk_keyboard.c $(COMMON_HEADERS) ps2* 
