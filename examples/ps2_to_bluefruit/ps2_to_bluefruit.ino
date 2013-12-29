#include <BluefruitHost.h>
#include <keyboard.h>
#include <host.h>

BluefruitHost host = BluefruitHost(&Serial1);

void setup() {
    keyboard_init();
    host_set_driver(host.asHostDriver());
}

void loop() {
    keyboard_task();
}
