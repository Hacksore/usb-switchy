#include <hidboot.h>
#include <usbhub.h>
#include <SPI.h>

#include "keyboard.h"
#include "mouse.h"

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

int activeArduino = 0;

const int MOUSE_MOVE = 0;
const int MOUSE_CLICK_LEFT = 1;
const int MOUSE_CLICK_RIGHT = 2;
const int BAUD_RATE = 115200;

void transmitData(byte payload[]) {
  if (activeArduino == 0) {
    Serial.write(payload, sizeof(payload));
  } else {
    #ifdef Serial1
      Serial1.write(payload, sizeof(payload));
    #endif
  }
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

USB Usb;
USBHub Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb);
MouseRptParser Prs;

void setup() {
  Serial.begin(BAUD_RATE);

  #ifdef Serial1
    Serial1.begin(BAUD_RATE);
  #endif

  while (!Serial);

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay(200);

  HidMouse.SetReportParser(0, &Prs);
}

void loop() {
  Usb.Task();
}
