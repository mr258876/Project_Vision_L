#ifndef _VISION_CONFIGURATIONS_H_
#define _VISION_CONFIGURATIONS_H_

#define VIDEO_FPS 30

#define LCD_WIDTH 240
#define LCD_HEIGHT 240

#define LCD_PIXEL_CLOCK_HZ (80 * 1000 * 1000)
#define LCD_CMD_BITS 8
#define LCD_PARAM_BITS 8

// Parameters for proximeter
#define PROX_THRS 210      // Proximeter interrupt threshold (Smaller value is further)
#define LCD_BRIGHTNESS 127 // Default screen brightness, Value in 0-255

// Parameters for accelerometer
#define ACC_SAMPLE_RATE 6.25 // Sample rate in HZ -> {0.781, 1.563, 3.125, 6.25, 12.5, 25, 50, 100, 200, 400, 800, 1600Hz}
#define ACC_RANGE 2          // Accelerometer range -> {2, 4, 8, 16g}
#define ACC_THRES 0.4        // Threshold of screen rotation
#define LOW_POWER            // Accelerometer Power mode -> {LOW_POWER, HIGH_RESOLUTION}

// MJPEG decoder settings
#define MJPEG_BUFFER_SIZE (240 * 240 * 2 / 8) // Screen resolution 240*240, 2 byte color, compression ratio 1:16

// LVGL Drive Letter
#define SD_DRIVE_LETTER 'S'
#define FLASH_DRIVE_LETTER 'F'

// Updating
#define UPDATE_FILE_PATH "/update.bin"

// JSON conf buffer size
#define JSON_CONF_BUFFER_SIZE 1024

/* Play List File */
#define PLAY_LIST_CONF_PATH "/playFiles.json"
#define PLAY_LIST_DEFAULT_CONF "{\"files\":[]}"
#define PLAY_LIST_CONF_DEFAULT_LENGTH 1024
#define PLAY_LIST_JSON_SIZE 1024

/* Hoyolab cookie */
#define HOYOLAB_CONF_PATH "/Hoyolab.json"
#define HOYOLAB_DEFAULT_CONF "{\"uid\":\"\", \"cookie\":\"\", \"device_guid\": \"\"}"
#define HOYOLAB_CONF_DEFAULT_LENGTH 1024
#define HOYOLAB_CONF_JSON_SIZE 1024

/* Weather conf file */
#define WEATHER_CONF_PATH "/Weather.json"
#define WEATHER_DEFAULT_CONF "{\"city\":\"\", \"latitude\":0.0, \"longitude\":0.0, \"provider\":1}"
#define WEATHER_CONF_DEFAULT_LENGTH 1024
#define WEATHER_CONF_JSON_SIZE 1024

/* Static file conf file */
#define STATIC_FILE_CONF_PATH "/The Vision L/static_resources.json"
#define STATIC_FILE_CONF_DEFAULT_LENGTH 8192
#define STATIC_FILE_CONF_JSON_SIZE 2048

/* Task Monitor */
// #define USE_TASK_MONITOR

/* OTA update */
#define OTA_STABLE_CHENNEL 0
#define OTA_BETA_CHANNEL 1
#define OTA_BUFFER_SIZE 1024
#define OTA_JSON_CONF_DEFAULT_LENGTH 1024
#define OTA_JSON_CONF_JSON_SIZE 1024
#define OTA_STABLE_CHANNEL_JSON_PATH "/update_stable.json"
#define OTA_BETA_CHANNEL_JSON_PATH "/update_beta.json"
#define OTA_STABLE_CHANNEL_RESOURCES_JSON_PATH "/s/The Vision L/static_resources.json"
#define OTA_BETA_CHANNEL_RESOURCES_JSON_PATH "/s/The Vision L/static_resources_beta.json"

///////////////////////////////////////

/* file extension helper function */
#define IS_FILE_EXT(filename, ext) \
    (strcasecmp(&filename[strlen(filename) - sizeof(ext) + 1], ext) == 0)

#endif // _VISION_CONFIGURATIONS_H_