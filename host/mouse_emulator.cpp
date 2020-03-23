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

void transmitData(uint16_t packet[]) {

  myTransfer.txBuff[0] = packet[0];

  if (packet[1] != NULL && packet[2] != NULL) {
    myTransfer.txBuff[1] = packet[1];
    myTransfer.txBuff[2] = packet[2];

    myTransfer.sendData(3);
    return;
  }
  
  myTransfer.sendData(1);
}

void MouseRptParser::OnMouseMove(MOUSEINFO *mi) {
  int mouseX = mi->dX;
  int mouseY = mi->dY;

  uint16_t payload[3] = {
    MOUSE_MOVE,
    mouseX,
    mouseY
  };

  transmitData(payload);

};

void MouseRptParser::OnLeftButtonUp (MOUSEINFO *mi) {
  uint16_t payload[1] = {
    MOUSE_UP_LEFT
  };

  transmitData(payload);
};

void MouseRptParser::OnLeftButtonDown (MOUSEINFO *mi) {
  uint16_t payload[1] = {
    MOUSE_DOWN_LEFT
  };

  transmitData(payload);
};

void MouseRptParser::OnRightButtonUp  (MOUSEINFO *mi) {
  uint16_t payload[1] = {
    MOUSE_UP_RIGHT
  };

  transmitData(payload);
};

void MouseRptParser::OnRightButtonDown  (MOUSEINFO *mi) {
  uint16_t payload[1] = {
    MOUSE_DOWN_RIGHT
  };

  transmitData(payload);
};

void MouseRptParser::OnMiddleButtonUp (MOUSEINFO *mi) {
  uint16_t payload[1] = {
    MOUSE_UP_MIDDLE
  };

  transmitData(payload);
};

void MouseRptParser::OnMiddleButtonDown (MOUSEINFO *mi) {
  uint16_t payload[1] = {
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
