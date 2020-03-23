#ifndef TASK_MQTT_AWS
#define TASK_MQTT_AWS

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <pgmspace.h>
#include <WiFi.h>
#include "../config/config.h"

#define MAX_MSG_SIZE_BYTES 900

MQTTClient mqtt = MQTTClient(MAX_MSG_SIZE_BYTES);
extern StoredValues gStoredValues;
WiFiClient net;

void keepMQTTonnectionAlive(void * parameter){
    for(;;){
        if(mqtt.connected()){
            mqtt.loop();
            vTaskDelay(500 / portTICK_PERIOD_MS);
            continue;
        }

        if(!WiFi.isConnected()){
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }

        serial_println(F("[MQTT] Connecting to MQTT..."));
        mqtt.begin(MQTT_ENDPOINT, net);

        long startAttemptTime = millis();
    
        while (!mqtt.connect(DEVICE_NAME) && (millis() - startAttemptTime < MQTT_CONNECT_TIMEOUT))
        {
            vTaskDelay(MQTT_CONNECT_DELAY);
        }

        if(!mqtt.connected()){
            lwmqtt_err_t lastError = mqtt.lastError();
            lwmqtt_return_code_t returnCode = mqtt.returnCode();
            serial_println("[MQTT] Last error:" + String(lastError) + " return code:" +String(returnCode));
            serial_println(F("[MQTT] MQTT connection timeout. Retry in 30s."));
            vTaskDelay(30000 / portTICK_PERIOD_MS);
        }

        serial_println(F("[MQTT] MQTT Connected!"));
    }
}

void mqttSending(void * parameter){
    // MQTT Sending
    for(;;){
        if(!WiFi.isConnected() || !mqtt.connected()){
            serial_println("[MQTT] MQTT: no connection. Discarding data..");
      }
      else {
        serial_print("[MQTT] MQTT publish number of breathes: ");
        serial_println(String(gStoredValues.breathes).c_str());
        mqtt.publish(MQTT_TOPIC_BREATHES, String(gStoredValues.breathes).c_str());

        // TODO : add more information on MQTT topics
      }

      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
      
}

#endif
