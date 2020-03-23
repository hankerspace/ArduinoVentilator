#ifndef ENUMS
#define ENUMS

#include <Arduino.h>

// The state in which the device can be. This mainly affects what
// is drawn on the display.
enum DEVICE_STATE {
  CONNECTING_WIFI,
  CONNECTING_MQTT,
  FETCHING_TIME,
  UP,
};

enum VENTILATOR_STATE {
  RELEASED,
  READY,
  WORKING
};

// Place to store all the variables that need to be Stored.
// All other functions should update these!
struct StoredValues {
  float durationBetweenBreathes;
  float breathDuration;
  float breatheIntensity;
  VENTILATOR_STATE ventilatorState;
  int breathes;
  int motorPosition;
  String workingTime;
  int8_t wifi_strength;
  DEVICE_STATE currentState;
  String time;
  bool releasePressed;
  bool workPressed;
};

#if DEBUG == true
  #define serial_print(x)  Serial.print (x)
  #define serial_println(x)  Serial.println (x)
#else
  #define serial_print(x)
  #define serial_println(x)
#endif

#endif