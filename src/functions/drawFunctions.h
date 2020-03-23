#ifndef DRAW_FUNCTIONS
#define DRAW_FUNCTIONS

 #include <WiFi.h>
#include "heltec.h"
 #include "../config/enums.h"
 #include "../config/config.h"

extern StoredValues gStoredValues;
extern unsigned char measureIndex;

void drawTime(){
    Heltec.display->drawString(0, 0, String(gStoredValues.time));
}

void drawSignalStrength(){
   const byte X = SCREEN_WIDTH - 20;
   const byte X_SPACING = 2;

  // Draw the four base rectangles
  Heltec.display->fillRect(X, 8-2, 1, 2);
  Heltec.display->fillRect(X + X_SPACING, 8-2, 1, 2);
  Heltec.display->fillRect(X + X_SPACING*2, 8-2, 1, 2);
  Heltec.display->fillRect(X + X_SPACING*3, 8-2, 1, 2);

  // Draw bar 2
  if(gStoredValues.wifi_strength > -70){
      Heltec.display->fillRect(X+X_SPACING, 8-4, 1, 4);
  }

  // Draw bar 3
  if(gStoredValues.wifi_strength > -60){
      Heltec.display->fillRect(X+X_SPACING*2, 8-6, 1, 6);
  }

  // Draw bar 4
  if(gStoredValues.wifi_strength >= -50){
      Heltec.display->fillRect(X+X_SPACING*3, 8-8, 1, 8);
  }
}

// /**
//  * The screen that is displayed when the ESP has just booted
//  * and is connecting to WiFi & MQTT.
//  */
void drawBootscreen(){
  byte X = 14;
  byte Y = 70;
  byte WIDTH = 6;
  byte MAX_HEIGHT = 35;
  byte HEIGHT_STEP = 10;
  byte X_SPACING = 10;

    Heltec.display->fillRect(X              , Y, WIDTH, MAX_HEIGHT - HEIGHT_STEP*3);
    Heltec.display->fillRect(X + X_SPACING  , Y - HEIGHT_STEP, WIDTH, MAX_HEIGHT - HEIGHT_STEP*2);
    Heltec.display->fillRect(X + X_SPACING*2, Y - HEIGHT_STEP*2, WIDTH, MAX_HEIGHT - HEIGHT_STEP);
    Heltec.display->fillRect(X + X_SPACING*3, Y - HEIGHT_STEP*3, WIDTH, MAX_HEIGHT);

  Heltec.display->drawString(0, Y + MAX_HEIGHT / 2, "Connecting");

  if(gStoredValues.currentState == CONNECTING_WIFI){
      Heltec.display->drawString(0, Y + MAX_HEIGHT / 2, "Connecting WiFi");
  }

  if(gStoredValues.currentState == CONNECTING_MQTT){
    Heltec.display->drawString(0, Y + MAX_HEIGHT / 2, "Connecting MQTT");
  }
}

// /**
//  * Draw the current informations in the middle of the display.
//  */
void drawScreenInformations(){

  String durationBetweenBreathes = String(gStoredValues.durationBetweenBreathes, 2);
  String breathDuration = String(gStoredValues.breathDuration, 2);
  String breatheIntensity = String(gStoredValues.breatheIntensity, 0);
  String breathes = String(gStoredValues.breathes);

  if(gStoredValues.ventilatorState == WORKING) {
    Heltec.display->drawString(0, 20, "WORKING " + gStoredValues.workingTime);
  }
  else if(gStoredValues.ventilatorState == READY) {
    Heltec.display->drawString(0, 20, "READY...");
  }
  else {
    Heltec.display->drawString(0, 20, "STAND BY...");
  }
  
  Heltec.display->drawString(0, 30, "D2B => " + durationBetweenBreathes + "ms");
  Heltec.display->drawString(0, 40, "BD => " + breathDuration + "ms");
  Heltec.display->drawString(0, 50, "BI => " + breatheIntensity );

}

#endif