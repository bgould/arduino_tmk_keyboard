TOP_DIR			=	.
TARGET_DIR		=	$(TOP_DIR)/KeyboardConverter
INTEGRATION_DIR	=	$(TARGET_DIR)/gluecode
EXAMPLES_DIR	=	$(TARGET_DIR)/examples
LIB_DIR			=	$(TOP_DIR)/lib
TMK_DIR			=	$(TOP_DIR)/tmk_keyboard
COMMON_DIR		= 	$(TMK_DIR)/common
PROTOCOL_DIR	=	$(TMK_DIR)/protocol

INTEGRATION_FILE=	$(INTEGRATION_DIR)/tmk_keyboard.c.inc

#		backlight.h \
#		bootloader.c \
#		bootloader.h \
#		bootmagic.h \

#		print.c \
#		print.h \
#		util.h 
#		serial.h \

COMMON_HEADERS	= 	report.h \
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

COMMON_SOURCES	=	keyboard.c \
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
					mousekey.c \

PROTOCOL_HEADERS=	ps2.h \

PROTOCOL_SOURCES=	ps2.c \

COMMON_FILES	=	$(COMMON_HEADERS) $(COMMON_SOURCES)
PROTOCOL_FILES	=	$(PROTOCOL_HEADERS) $(PROTOCOL_SOURCES)
TMK_FILES		=	$(COMMON_FILES) $(PROTOCOL_FILES)

LIB_SOURCES		=	BluefruitHost.cpp \
					KeyboardConverter.cpp \
					KeyboardReport.cpp \
					MouseReport.cpp \
					KeyboardHost.cpp

TARGETS			= 	$(patsubst %, $(TARGET_DIR)/%, $(COMMON_SOURCES) $(PROTOCOL_SOURCES) $(LIB_SOURCES))

PROTOCOLS		=	ps2_matrix terminal_matrix

EXAMPLES		=	ps2_to_bluefruit terminal_to_bluefruit

TMK_INCLUDE		=	printf '\#include "tmk_keyboard.h"\n'

all: clean $(TARGETS) $(TARGET_DIR)/print.h examples

$(TARGET_DIR)/%.c: $(INTEGRATION_FILE)
	@echo "" >> $(INTEGRATION_FILE); 
	@echo "#ifndef TMK_SOURCE_$*_H__" >> $(INTEGRATION_FILE); 
	@echo "#define TMK_SOURCE_$*_H__ 1" >> $(INTEGRATION_FILE); 
	cat $(TARGET_DIR)/$*.c >> $(INTEGRATION_FILE);
	@echo "" >> $(INTEGRATION_FILE); 
	@echo "#endif" >> $(INTEGRATION_FILE);
	@rm $(TARGET_DIR)/$*.c;

$(INTEGRATION_FILE): copy-tmk-files
	@touch $(INTEGRATION_FILE);
	@rm $(INTEGRATION_FILE);
	@echo '#include "tmk_keyboard.h"' >> $(INTEGRATION_FILE);
#	@echo '#include "config.h"' >> $(INTEGRATION_FILE);
	@echo '' >> $(INTEGRATION_FILE);

$(TARGET_DIR)/%.cpp: init $(LIB_DIR)/%.cpp
	cp $(LIB_DIR)/$*.cpp $(LIB_DIR)/$*.h $(TARGET_DIR)

$(TARGET_DIR)/Keyboard%.h: init $(LIB_DIR)/Keyboard%.h
	cp $(LIB_DIR)/Keyboard$*.h $(TARGET_DIR)
	
$(TARGET_DIR)/print.h: init
	cp $(LIB_DIR)/print.h $(TARGET_DIR)

copy-tmk-files: init
	cp $(patsubst %, $(COMMON_DIR)/% ,$(COMMON_FILES)) $(patsubst %, $(PROTOCOL_DIR)/%,$(PROTOCOL_FILES)) $(TARGET_DIR)

%_matrix: init
	@mkdir $(INTEGRATION_DIR)/$@
	cp $(TMK_DIR)/converter/$*_usb/* $(INTEGRATION_DIR)/$@
	cp $(LIB_DIR)/tmk_keyboard.h $(INTEGRATION_DIR)/$@

examples: init ps2_to_bluefruit terminal_to_bluefruit
	
ps2_to_bluefruit: ps2_matrix
	cp -R $(TOP_DIR)/examples/$@ $(TARGET_DIR)/examples
	#$(TMK_INCLUDE) >> $(TARGET_DIR)/examples/$@/keymap_jis.c; cat $(INTEGRATION_DIR)/$</keymap_jis.c >> $(TARGET_DIR)/examples/$@/keymap_jis.c;
	#$(TMK_INCLUDE) >> $(TARGET_DIR)/examples/$@/matrix.c; cat $(INTEGRATION_DIR)/$</matrix.c >> $(TARGET_DIR)/examples/$@/matrix.c;
	#$(TMK_INCLUDE) >> $(TARGET_DIR)/examples/$@/led.c;    cat $(INTEGRATION_DIR)/$</led.c    >> $(TARGET_DIR)/examples/$@/led.c;
	cp $(INTEGRATION_FILE) $(TARGET_DIR)/examples/$@/tmk_keyboard.c
	#cp $(INTEGRATION_DIR)/$</config.h $(TARGET_DIR)/examples/$@
	cp $(INTEGRATION_DIR)/$</tmk_keyboard.h $(TARGET_DIR)/examples/$@

terminal_to_bluefruit: terminal_matrix
	cp -R $(TOP_DIR)/examples/$@ $(TARGET_DIR)/examples
	#$(TMK_INCLUDE) >> $(TARGET_DIR)/examples/$@/keymap.c; cat $(INTEGRATION_DIR)/$</keymap.c >> $(TARGET_DIR)/examples/$@/keymap.c;
	#$(TMK_INCLUDE) >> $(TARGET_DIR)/examples/$@/matrix.c; cat $(INTEGRATION_DIR)/$</matrix.c >> $(TARGET_DIR)/examples/$@/matrix.c;
	#$(TMK_INCLUDE) >> $(TARGET_DIR)/examples/$@/led.c;    cat $(INTEGRATION_DIR)/$</led.c    >> $(TARGET_DIR)/examples/$@/led.c;
	cp $(INTEGRATION_FILE) $(TARGET_DIR)/examples/$@/tmk_keyboard.c
	#cp $(INTEGRATION_DIR)/$</config.h $(TARGET_DIR)/examples/$@
	cp $(INTEGRATION_DIR)/$</tmk_keyboard.h $(TARGET_DIR)/examples/$@

init:
	@mkdir -p $(INTEGRATION_DIR)
	@mkdir -p $(EXAMPLES_DIR)

clean:
	rm -Rf $(TARGET_DIR)
