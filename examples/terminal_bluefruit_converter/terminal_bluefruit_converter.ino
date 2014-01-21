#include "config.h"
#include <SoftwareSerial.h>
#include <KeyboardFirmware.h>

BluefruitHost host;
PS2MatrixCodeset3 matrix;

void setup() {

#if DEBUG_ENABLE
  while (!Serial) ;
  KeyboardDebug.println("started logging");
#endif
  
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  delay(2000);
  KeyboardFirmware.begin(host, matrix);
}

void loop() {
    KeyboardFirmware.runTask();
}
