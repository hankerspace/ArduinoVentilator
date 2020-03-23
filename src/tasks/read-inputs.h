#ifndef TASK_READ_INPUTS
#define TASK_READ_INPUTS

#include <Arduino.h>

#include "../config/config.h"
#include "../config/enums.h"

extern StoredValues gStoredValues;

void readInputs(void * parameter)
{
    for(;;){
      //serial_println("[INPUTS] Measuring...");

      // TODO : maybe add some good factors ?
      gStoredValues.durationBetweenBreathes = analogRead(ADC_POT_DURATION_BETWEEN_BREATHES) / 10;
      gStoredValues.breathDuration = analogRead(ADC_POT_BREATH_DURATION) / 10;
      gStoredValues.breatheIntensity = analogRead(ADC_POT_BREATHE_INTENSITY) / 10;
      if(digitalRead(GPIO_BT_WORK)) {
        gStoredValues.workPressed = true; 
      }
      else {
        gStoredValues.workPressed = false;
      }
      if(digitalRead(GPIO_BT_RELEASE)) {
        gStoredValues.releasePressed = true; 
      }
      else {
        gStoredValues.releasePressed = false;
      }

      gStoredValues.motorPosition = analogRead(ADC_MOTOR_INPUT);

      vTaskDelay(10 / portTICK_PERIOD_MS);
    }    
}

#endif
