#include "mouse_emulator.h"
#include "SerialTransfer.h"

#include <hidboot.h>
#include <usbhub.h>
#include <SPI.h>
#include <myutil.h>

const int BAUD_RATE = 9600;

////////////////////////////
class MouseRptParser : public MouseReportParser {
protected:
  void OnMouseMove  (MOUSEINFO *mi);
  void OnLeftButtonUp (MOUSEINFO *mi);
  void OnLeftButtonDown (MOUSEINFO *mi);
  void OnRightButtonUp  (MOUSEINFO *mi);
  void OnRightButtonDown  (MOUSEINFO *mi);
  void OnMiddleButtonUp (MOUSEINFO *mi);
  void OnMiddleButtonDown (MOUSEINFO *mi);
};

// INSTANCES
USB Usb;
USBHub Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb);
MouseRptParser Prs;
SerialTransfer myTransfer;

void transmitData(uint8_t packet[]) {
  int arrayLength = sizeof(packet) / sizeof(uint8_t);

  for(int i=0; i<arrayLength; i++){
    myTransfer.txBuff[i] = packet[i];
  }
  
  myTransfer.sendData(arrayLength);
}

void MouseRptParser::OnMouseMove(MOUSEINFO *mi) {
  int mouseX = mi->dX;
  int mouseY = mi->dY;

  uint8_t payload[3] = {
    MOUSE_MOVE,
    char(mouseX),
    char(mouseY)
  };

  transmitData(payload);

};

void MouseRptParser::OnLeftButtonUp (MOUSEINFO *mi) {
  uint8_t payload[1] = {
    MOUSE_UP_LEFT
  };

  transmitData(payload);
};

void MouseRptParser::OnLeftButtonDown (MOUSEINFO *mi) {
  uint8_t payload[1] = {
    MOUSE_DOWN_LEFT
  };

  transmitData(payload);
};

void MouseRptParser::OnRightButtonUp  (MOUSEINFO *mi) {
  uint8_t payload[1] = {
    MOUSE_UP_RIGHT
  };

  transmitData(payload);
};

void MouseRptParser::OnRightButtonDown  (MOUSEINFO *mi) {
  uint8_t payload[1] = {
    MOUSE_DOWN_RIGHT
  };

  transmitData(payload);
};

void MouseRptParser::OnMiddleButtonUp (MOUSEINFO *mi) {
  uint8_t payload[1] = {
    MOUSE_UP_MIDDLE
  };

  transmitData(payload);
};

void MouseRptParser::OnMiddleButtonDown (MOUSEINFO *mi) {
  uint8_t payload[1] = {
    MOUSE_DOWN_MIDDLE
  };

  transmitData(payload);
};


MouseEmulator::MouseEmulator() {
  // contructor
}

void MouseEmulator::begin() {
  Serial.begin(BAUD_RATE);
  myTransfer.begin(Serial);

  Usb.Init();
  delay(200);
  
  HidMouse.SetReportParser(0, &Prs);
}

void MouseEmulator::loop() {
  Usb.Task();
  
}
