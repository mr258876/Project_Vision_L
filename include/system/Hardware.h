#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include <Arduino.h>
#include "LCDPanels.h"

struct Pinout
{
    // LCD Pins (Use -1 for enpty pins)
    uint8_t LCD_BL;
    uint8_t LCD_DC;
    uint8_t LCD_RST;
    uint8_t LCD_CS;
    uint8_t LCD_CLK;
    uint8_t LCD_MOSI;
    uint8_t LCD_MISO;

    // LCD Panel type
    LCD_panel_t LCD_panel;
    spi_host_device_t LCD_spi_host;
    uint32_t LCD_clock_speed;
    bool LCD_shared_spi;

    // SD Card Pins (Use NULL for enpty pins)
    uint8_t SD_DAT2;
    uint8_t SD_DAT3;
    uint8_t SD_CMD;
    uint8_t SD_CLK;
    uint8_t SD_DAT0;
    uint8_t SD_DAT1;

    // SD Card Bus
    bool SD_use_sdmmc;
    bool SD_use_1_bit;

    // I2C Pins (Use NULL for enpty pins)
    uint8_t I2C_SCL;
    uint8_t I2C_SDA;

    // Inturrupt Pins (Use NULL for enpty pins)
    uint8_t PWR_BTN;
    uint8_t PROX_INT;
    uint8_t ACCL_INT;

    // Others
    uint8_t AUDIO_OUT;
};

uint8_t getHWType();
void getVisionPinout(Pinout *po, uint8_t hw_type);

#endif