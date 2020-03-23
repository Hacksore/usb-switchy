#ifndef Mouse_Emulator_h
#define Mouse_Emulator_h

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class MouseEmulator  {
  public:
    // Constructor 
    MouseEmulator();

    // Methods
    void begin();
    void loop();
};
#endif
