#include "Hardware.h"

uint8_t getHWType()
{
    digitalWrite(26, INPUT_PULLUP);
    if (digitalRead(26) == LOW)
        // 璃月神之眼挂件 Extended
        // https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended
        return 1;

    digitalWrite(23, INPUT_PULLUP);
    if (digitalRead(23) == LOW)
        // 璃月神之眼挂件
        // https://oshwhub.com/Myzhazha/li-yue-shen-zhi-yan-gua-jian
        return 2;

    digitalWrite(16, INPUT_PULLUP);
    if (digitalRead(16) == LOW)
        // 神之眼挂件V1.2_ESP32U
        // https://oshwhub.com/Myzhazha/shen-zhi-yan-gua-jian-v1-2_esp32u
        return 3;
    
    return 0;
}

void getVisionPinout(Pinout *po, uint8_t hw_type)
{
    switch (hw_type)
    {
    case 2:
        // 璃月神之眼挂件
        // https://oshwhub.com/Myzhazha/li-yue-shen-zhi-yan-gua-jian
        po->LCD_BL = 22;
        po->LCD_DC = 27;
        po->LCD_RST = 33;
        po->LCD_CS = 5;
        po->LCD_CLK = 14;  // SCL
        po->LCD_MOSI = 15; // SDA
        po->LCD_panel = LCD_ST7789;
        po->LCD_clock_speed = 40000000;
        po->LCD_shared_spi = true;
        po->SD_DAT2 = NULL;
        po->SD_DAT3 = 13;
        po->SD_CMD = 15;
        po->SD_CLK = 14;
        po->SD_DAT0 = 2;
        po->SD_DAT1 = NULL;
        po->SD_use_sdmmc = true;
        po->SD_use_1_bit = true;
        po->I2C_SCL = NULL;
        po->I2C_SDA = NULL;
        po->PWR_BTN = 23;
        po->PROX_INT = NULL;
        po->ACCL_INT = NULL;
        po->AUDIO_OUT = NULL;
        break;

    case 3:
        // 神之眼挂件V1.2_ESP32U
        // https://oshwhub.com/Myzhazha/shen-zhi-yan-gua-jian-v1-2_esp32u
        po->LCD_BL = 22;
        po->LCD_DC = 27;
        po->LCD_RST = 33;
        po->LCD_CS = 5;
        po->LCD_CLK = 14;  // SCL
        po->LCD_MOSI = 15; // SDA
        po->LCD_panel = LCD_GC9A01;
        po->LCD_clock_speed = 40000000;
        po->LCD_shared_spi = true;
        po->SD_DAT2 = NULL;
        po->SD_DAT3 = 13;
        po->SD_CMD = 15;
        po->SD_CLK = 14;
        po->SD_DAT0 = 2;
        po->SD_DAT1 = NULL;
        po->SD_use_sdmmc = true;
        po->SD_use_1_bit = true;
        po->I2C_SCL = NULL;
        po->I2C_SDA = NULL;
        po->PWR_BTN = 16;
        po->PROX_INT = NULL;
        po->ACCL_INT = NULL;
        po->AUDIO_OUT = NULL;
        break;

    default:
        // 璃月神之眼挂件 Extended
        // https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended
        po->LCD_BL = 32;
        po->LCD_DC = 27;
        po->LCD_RST = 33;
        po->LCD_CS = 5;
        po->LCD_CLK = 18;  // SCL
        po->LCD_MOSI = 23; // SDA
        po->LCD_panel = LCD_ST7789;
        po->LCD_clock_speed = 80000000;
        po->LCD_shared_spi = false;
        po->SD_DAT2 = 12;
        po->SD_DAT3 = 13;
        po->SD_CMD = 15;
        po->SD_CLK = 14;
        po->SD_DAT0 = 2;
        po->SD_DAT1 = 4;
        po->SD_use_sdmmc = true;
        po->SD_use_1_bit = false;
        po->I2C_SCL = 22;
        po->I2C_SDA = 21;
        po->PWR_BTN = 26;
        po->PROX_INT = 35;
        po->ACCL_INT = NULL;
        po->AUDIO_OUT = 25;
        break;
    }
}
