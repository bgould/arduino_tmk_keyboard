#include "KeyboardConverter.h"
#include "BluefruitHost.h"

BluefruitHost host = BluefruitHost(&Serial1);
KeyboardConverter converter = KeyboardConverter(&host);

void setup() {
    converter.init();
}

void loop() {
    converter.run_task();
}
