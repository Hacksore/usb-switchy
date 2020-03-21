#include "Mouse.h"

void setup() {
  Serial.begin(115200);  
  Mouse.begin();  
}

void loop() {
  if (Serial.available() > 0) {
    // TODO: convert this to the proper data to use for keyboard
    incomingByte = Serial.read();
  } 
}
