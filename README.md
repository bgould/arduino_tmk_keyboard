arduino_tmk_keyboard
====================

Simple (and incomplete) Arduino/C++ wrapper for the fantastic [TMK Keyboard Firmware](http://github.com/tmk/tmk_keyboard)

This implementation is "incomplete" because at the moment the only provided protocol is PS/2, and the only host implementation is for the excellent Bluefruit EZ-Key HID from Adafruit Industries.

If you have the ability to compile &amp; load AVR C code onto your microcontroller, there is nothing that this library provides that you could not do directly with tmk_keyboard.  However you may be interested in this project if you want to:
* compile and load keyboard or converter firmware in the Arduino IDE
* utilize object oriented techniques to create new implementations of the tmk_keyboard components (host, matrix, etc)
* utilize other Arduino libraries in custom tmk_keyboard action functions
* allow your Arduino project to utilize existing keyboard or mouse hardware for input
* make your Arduino project appear as a keyboard or mouse to a PC without special drivers, including the BIOS at boot time
* utilize functionality not found in the standard Keyboard/Mouse libraries on Leonardo such as consumer and system keys
 
So far this wrapper has been developed for a specific project, but I will expand it and make it more configurable in the future.  In short order I plan to integrate TMK's functionality for:
* mouse keys
* V-USB host implementation
* PJRC host implementation (if possible)
 
"Internal" components (such as protocols, command, bootmagic, etc) are integrated using their native C implementations.

"API" components (such as hosts, matrices, and keymaps) are refactored into a C++ object heirarchy to allow for easier customization & implementation within the Arduino IDE.

To get started, download this project as a zip file and put it in your Arduino libraries folder.  You can use the [terminal_bluefruit_converter] (https://github.com/bgould/arduino-tmk-keyboard/blob/master/examples/terminal_bluefruit_converter/terminal_bluefruit_converter.ino) example to see an example of how to utilize this library to build a bluetooth converter for a terminal Model M keyboard.

Resources:
* [EZ-Key HID Tutorial at learn.adafruit.com](http://learn.adafruit.com/introducing-bluefruit-ez-key-diy-bluetooth-hid-keyboard)
* [TMK Keyboard Firmware](http://github.com/tmk/tmk_keyboard)
