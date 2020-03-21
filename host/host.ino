#include "mouse_emulator.h"

MouseEmulator mouseEmulator = MouseEmulator();
void setup() {
  mouseEmulator.begin();
}

void loop() {
  mouseEmulator.loop();
}
