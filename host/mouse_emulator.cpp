#include "mouse_emulator.h"

#include <hidboot.h>
#include <usbhub.h>
#include <SPI.h>

// CONSTANTS
const int MOUSE_MOVE = 0;
const int MOUSE_CLICK_LEFT = 1;
const int MOUSE_CLICK_RIGHT = 2;
const int BAUD_RATE = 115200;

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

void transmitData(byte payload[]) {
  // TODO: where do I keep track of active arduino?
  Serial.write(payload, sizeof(payload));
}

void MouseRptParser::OnMouseMove(MOUSEINFO *mi) {
  int mouseX = mi->dX;
  int mouseY = mi->dY;

  byte payload[3] = {
    MOUSE_MOVE,
    mouseX,
    mouseY
  };

  transmitData(payload);

};

void MouseRptParser::OnLeftButtonUp (MOUSEINFO *mi) {

};

void MouseRptParser::OnLeftButtonDown (MOUSEINFO *mi) {
  byte payload[1] = {
    MOUSE_CLICK_LEFT      
  };

  transmitData(payload);
};

void MouseRptParser::OnRightButtonUp  (MOUSEINFO *mi) {

};

void MouseRptParser::OnRightButtonDown  (MOUSEINFO *mi) {

};

void MouseRptParser::OnMiddleButtonUp (MOUSEINFO *mi) {

};

void MouseRptParser::OnMiddleButtonDown (MOUSEINFO *mi) {

};
//////////////


// INSTANCES
USB Usb;
USBHub Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb);
MouseRptParser Prs;

MouseEmulator::MouseEmulator() {
  // contructor
}

void MouseEmulator::begin() {
  Serial.begin(115200);

  while (!Serial);
  
  Serial.println("MouseEmulator begin successfully.");

  Usb.Init();

  delay(200);
  
  HidMouse.SetReportParser(0, &Prs);
}

void MouseEmulator::loop() {
  Usb.Task();
}
