#ifndef CONFIG
#define CONFIG

/**
 * Set this to false to disable Serial logging
 */
#define DEBUG true

/**
 * The name of this device 
 * Also used to set the hostname on the network
 */
#define DEVICE_NAME "ESP32OpenVentilator"

/**
 * ADC input pin that is used to read out the pententiometer values
 */
#define ADC_POT_DURATION_BETWEEN_BREATHES 36
#define ADC_POT_BREATH_DURATION 37
#define ADC_POT_BREATHE_INTENSITY 38

/**
 * GPIO input pin for pressbutton values
 */
#define GPIO_BT_WORK 10
#define GPIO_BT_RELEASE 11

/**
 * ADC output pin that is used to control motor
 */
#define ADC_MOTOR_OUTPUT 34
#define ADC_MOTOR_INPUT 39

/**
 * Motor max/min positions
 */
#define MOTOR_RELEASED_POS 0
#define MOTOR_READY_POS 1000
#define MOTOR_WORKING_MIN 2000
#define MOTOR_WORKING_MAX 3000

/**
 * WiFi credentials
 */
#define WIFI_NETWORK "CUIR"
#define WIFI_PASSWORD "****"

/**
 * Timeout for the WiFi connection. When this is reached,
 * the ESP goes into deep sleep for 30seconds to try and
 * recover.
 */
#define WIFI_TIMEOUT 20000 // 20 seconds

/**
 * How long should we wait after a failed WiFi connection
 * before trying to set one up again.
 */
#define WIFI_RECOVER_TIME_MS 20000 // 20 seconds

/**
 * Dimensions of the OLED display attached to the ESP
 */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

/**
 * The MQTT endpoint of the service we should connect to and receive messages
 * from.
 */
#define MQTT_ENDPOINT "192.168.86.40"
#define MQTT_TOPIC_BREATHES "ventilator/nbBreathes"

#define MQTT_CONNECT_DELAY 200
#define MQTT_CONNECT_TIMEOUT 20000 // 20 seconds


/**
 * Syncing time with an NTP server
 */
#define NTP_TIME_SYNC_ENABLED true
#define NTP_SERVER "pool.ntp.org"
#define NTP_OFFSET_SECONDS 3600
#define NTP_UPDATE_INTERVAL_MS 60000

// Check which core Arduino is running on. This is done because updating the 
// display only works from the Arduino core.
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#endif
