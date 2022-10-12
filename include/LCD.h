#ifndef _LCD_H_
#define _LCD_H_

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "conf.h"

typedef enum
{
    LCD_ST7789 = 0,
    LCD_GC9A01
} LCD_panel_t;

void LCDinit(LGFX_Device *gfx, LCD_panel_t lcd_type, uint8_t LCD_DC, uint8_t LCD_RST, uint8_t LCD_CS, uint8_t LCD_CLK, uint8_t LCD_MOSI, bool isSharedSPI, uint32_t LCD_clock_speed);

#endif