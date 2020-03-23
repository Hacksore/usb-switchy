#include "SerialTransfer.h"
#include "Mouse.h"
#include <myutil.h>

// define the packet lib
SerialTransfer myTransfer;

void setup() {

  // init the mouse lib
  Mouse.begin();

  // testing with the MKR1000 which uses Serial1
  // need to expierment with increasing this speed
  Serial1.begin(9600);
  myTransfer.begin(Serial1);

}

void loop() {
  if(myTransfer.available()) {
    int instruction = myTransfer.rxBuff[0];

    switch(instruction) {
      case MOUSE_MOVE:
      {
        int x = myTransfer.rxBuff[1];
        int y = myTransfer.rxBuff[2];
        Mouse.move(x, y);
        break;
      }
      case MOUSE_DOWN_LEFT:
        Mouse.press(0);
        break;
      case MOUSE_UP_LEFT:
        Mouse.release(0);
        break;
      case MOUSE_DOWN_RIGHT:
        Mouse.press(1);
        break;
      case MOUSE_UP_RIGHT:
        Mouse.release(1);
        break;
    }
    
  }

}
