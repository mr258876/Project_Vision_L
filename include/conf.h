#ifndef _VISION_CONFIGURATIONS_H_
#define _VISION_CONFIGURATIONS_H_

#define VIDEO_FPS 30

// LCD screen Pinout
#define LCD_BL 32
#define LCD_DC 27
#define LCD_RST 33
#define LCD_CS 5
#define LCD_CLK 18  // SCL
#define LCD_MISO 19 // Unused
#define LCD_MOSI 23 // SDA

#define LCD_WIDTH 240
#define LCD_HEIGHT 240

#define LCD_PIXEL_CLOCK_HZ (80 * 1000 * 1000)
#define LCD_CMD_BITS           8
#define LCD_PARAM_BITS         8

// SD Card Pinout
#define DAT2 12
#define DAT3 13
#define CMD 15
#define CLK 14
#define DAT0 2
#define DAT1 4

// SD Card Bus
// #define _CONFIG_SD_USE_SPI_
// #define _CONFIG_SD_USE_SDMMC_1BIT_
#define _CONFIG_SD_USE_SDMMC_4BIT_

// SD Card Class Name
#if defined(_CONFIG_SD_USE_SPI_)
#define SD_CLASS SD
#elif defined(_CONFIG_SD_USE_SDMMC_1BIT_)
#define SD_CLASS SD_MMC
#elif defined(_CONFIG_SD_USE_SDMMC_4BIT_)
#define SD_CLASS SD_MMC
#endif

// Proximiter / Lightingmeter type
#define _CONFIG_PROX_LIGHT_USE_APDS9930_
// #define _CONFIG_PROX_LIGHT_USE_APDS9960_

// Parameters for proximeter
#define PROX_INT 35 // Proximeter interrupt pin

#ifdef _CONFIG_PROX_LIGHT_USE_APDS9960_
#define PROX_LIGHT_METER APDS9960
#define PROX_THRS 120      // Proximeter interrupt threshold (Smaller value is further)
#define LCD_BRIGHTNESS 127 // Default screen brightness, Value in 0-255
#elif defined( _CONFIG_PROX_LIGHT_USE_APDS9930_)
#define PROX_LIGHT_METER APDS9930
#define PROX_THRS 210      // Proximeter interrupt threshold (Smaller value is further)
#define LCD_BRIGHTNESS 127 // Default screen brightness, Value in 0-255
#endif

// Parameters for accelerometer
#define ACC_SAMPLE_RATE 6.25 // Sample rate in HZ -> {0.781, 1.563, 3.125, 6.25, 12.5, 25, 50, 100, 200, 400, 800, 1600Hz}
#define ACC_RANGE 2          // Accelerometer range -> {2, 4, 8, 16g}
#define ACC_THRES 0.4        // Threshold of screen rotation
#define LOW_POWER            // Accelerometer Power mode -> {LOW_POWER, HIGH_RESOLUTION}

// MJPEG decoder settings
#define MJPEG_BUFFER_SIZE (240 * 240 * 2 / 12) // Screen resolution 240*240, 2 byte color, compression ratio 1:16

// Button Pin settings
#define BUTTON_PIN 26

// LVGL Drive Letter
#define DRIVE_LETTER 'S'

// Audio Output Pin
#define AUDIO_OUT 25

// Time settings
#define GMTOFFSET 28800
#define DAYLIGHTOFFSET 0

// Updating
#define UPDATE_FILE_PATH "/update.bin"

// JSON conf buffer size
#define JSON_CONF_BUFFER_SIZE 1024

/* Play File List */
#define PLAY_FILE_CONF_PATH "/playFiles.json"
#define PLAY_FILE_DEFAULT_CONF "{\"files\":[\"S:/Pyro.mjpeg\",\"S:/Hydro.mjpeg\",\"S:/Anemo.mjpeg\",\"S:/Electro.mjpeg\",\"S:/Dendro.mjpeg\",\"S:/Cryo.mjpeg\",\"S:/Geo.mjpeg\"]}"

/* Hoyolab cookie */
#define HOYOLAB_CONF_PATH "/Hoyolab.json"
#define HOYOLAB_DEFAULT_CONF "{\"uid\":\"\", \"cookie\":\"\"}"

#endif // _VISION_CONFIGURATIONS_H_