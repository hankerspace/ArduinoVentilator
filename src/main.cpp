#include <Arduino.h>
#include "heltec.h"
#include <SPI.h>
#include <Wire.h>
#include "EmonLib.h"
#include <driver/adc.h>

#include "config/config.h"
#include "config/enums.h"

#include "tasks/fetch-time-from-ntp.h"
#include "tasks/mqtt-sending.h"
#include "tasks/motor-management.h"
#include "tasks/wifi-connection.h"
#include "tasks/wifi-update-signalstrength.h"
#include "tasks/read-inputs.h"
#include "tasks/updateDisplay.h"


StoredValues gStoredValues;

void setup()
{
  Serial.begin(115200);

  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, false /*Serial Disable*/);

  // Setup the inputs/outputs
  pinMode(ADC_POT_DURATION_BETWEEN_BREATHES, INPUT);
  pinMode(ADC_POT_BREATH_DURATION, INPUT);
  pinMode(ADC_POT_BREATHE_INTENSITY, INPUT);
  pinMode(GPIO_BT_WORK, INPUT);
  pinMode(GPIO_BT_RELEASE, INPUT);
  pinMode(ADC_MOTOR_INPUT, INPUT);
  pinMode(ADC_MOTOR_OUTPUT, OUTPUT);

  // ----------------------------------------------------------------
  // TASK: Connect to WiFi & keep the connection alive.
  // ----------------------------------------------------------------
  xTaskCreatePinnedToCore(
    keepWiFiAlive,
    "keepWiFiAlive",  // Task name
    5000,            // Stack size (bytes)
    NULL,             // Parameter
    1,                // Task priority
    NULL,             // Task handle
    ARDUINO_RUNNING_CORE
  );

  // ----------------------------------------------------------------
  // TASK: Connect to MQTT & keep the connection alive.
  // ----------------------------------------------------------------
  xTaskCreate(
    keepMQTTonnectionAlive,
    "MQTT",      // Task name
    5000,            // Stack size (bytes)
    NULL,             // Parameter
    5,                // Task priority
    NULL              // Task handle
  );

  // ----------------------------------------------------------------
  // TASK: Send MQTT values periodically.
  // ----------------------------------------------------------------
  xTaskCreate(
    mqttSending,
    "MQTT sending",      // Task name
    5000,            // Stack size (bytes)
    NULL,             // Parameter
    8,                // Task priority
    NULL              // Task handle
  );

  // ----------------------------------------------------------------
  // TASK: Update the display every second
  //       This is pinned to the same core as Arduino
  //       because it would otherwise corrupt the OLED
  // ----------------------------------------------------------------
  xTaskCreatePinnedToCore(
    updateDisplay,
    "UpdateDisplay",  // Task name
    10000,            // Stack size (bytes)
    NULL,             // Parameter
    3,                // Task priority
    NULL,             // Task handle
    ARDUINO_RUNNING_CORE
  );

  // ----------------------------------------------------------------
  // Task: read inputs from potentiometers and button
  // ----------------------------------------------------------------
  xTaskCreate(
    readInputs,
    "Read inputs",  // Task name
    10000,                  // Stack size (bytes)
    NULL,                   // Parameter
    4,                      // Task priority
    NULL                    // Task handle
  );

  // ----------------------------------------------------------------
  // Task: manage motor
  // ----------------------------------------------------------------
  xTaskCreate(
    manageMotor,
    "Motor management",  // Task name
    1000,                  // Stack size (bytes)
    NULL,                   // Parameter
    7,                      // Task priority
    NULL                    // Task handle
  );

  // ----------------------------------------------------------------
  // TASK: update time from NTP server.
  // ----------------------------------------------------------------
  #if NTP_TIME_SYNC_ENABLED == true
    xTaskCreate(
      fetchTimeFromNTP,
      "Update NTP time",
      5000,            // Stack size (bytes)
      NULL,             // Parameter
      1,                // Task priority
      NULL              // Task handle
    );
  #endif

  // ----------------------------------------------------------------
  // TASK: update WiFi signal strength
  // ----------------------------------------------------------------
  xTaskCreate(
    updateWiFiSignalStrength,
    "Update WiFi strength",
    1000,             // Stack size (bytes)
    NULL,             // Parameter
    2,                // Task priority
    NULL              // Task handle
  );

}

void loop()
{
    vTaskDelay(10000 / portTICK_PERIOD_MS);
}