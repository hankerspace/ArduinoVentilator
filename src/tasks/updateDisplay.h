#ifndef TASK_UPDATE_DISPLAY
#define TASK_UPDATE_DISPLAY

#include <Arduino.h>
#include "heltec.h"
#include "functions/drawFunctions.h"
#include "../config/config.h"

extern StoredValues gStoredValues;

/**
 * Metafunction that takes care of drawing all the different
 * parts of the display (or not if it's turned off).
 */
void updateDisplay(void * parameter){
  for (;;){
    serial_println(F("[LCD] Updating..."));
    Heltec.display->clear();

    if(gStoredValues.currentState == CONNECTING_WIFI || 
        gStoredValues.currentState == CONNECTING_MQTT){
      drawBootscreen();
    }
    
    if(gStoredValues.currentState == UP){
      drawTime();
      drawSignalStrength();
      drawScreenInformations();
    }

    Heltec.display->display();

    // Sleep for 2 seconds, then update display again!
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

#endif
