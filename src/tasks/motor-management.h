#ifndef TASK_MOTOR_MANAGEMENT
#define TASK_MOTOR_MANAGEMENT

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include "../config/config.h"

extern StoredValues gStoredValues;

bool releaseInProgress = false;
bool readyInProgress = false;
bool pressing = true;

void manageMotor(void * parameter){
    for(;;){
        int motorPos = gStoredValues.motorPosition;
        int newMotorPos = motorPos;

        // Manage motor release
        if(gStoredValues.releasePressed) releaseInProgress = true;
        if(releaseInProgress && motorPos <= MOTOR_RELEASED_POS){
            releaseInProgress = false;
            gStoredValues.ventilatorState = RELEASED;
        } 
        else if (releaseInProgress && motorPos > MOTOR_RELEASED_POS) {
            newMotorPos--;
        }
        
        // Manage motor to ready 
        if(gStoredValues.workPressed) readyInProgress = true;
        if(readyInProgress && motorPos == MOTOR_READY_POS){
            readyInProgress = false;
            gStoredValues.ventilatorState = READY;
        } 
        else if (readyInProgress && motorPos != MOTOR_READY_POS) {
            newMotorPos++;
        }

        // Manage motor ready to woking mode
        if(gStoredValues.ventilatorState == READY) {
            gStoredValues.ventilatorState = WORKING;
        }

        // Manage motor working mode
        // TODO : use breath intensity , duration, etc... to manage motor in a better way
        if(gStoredValues.ventilatorState == WORKING) {
            if(motorPos > MOTOR_WORKING_MIN && motorPos < MOTOR_WORKING_MAX) {
                // In range
                if(pressing) {
                    newMotorPos++;
                }
                else {
                    newMotorPos--;
                }
            }
            else if (motorPos > MOTOR_WORKING_MAX) {
                pressing = false;
                gStoredValues.breathes++;
            }
            else if (motorPos < MOTOR_WORKING_MIN) {
                pressing = true;
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

#endif
