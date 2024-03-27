
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#elif defined(LV_BUILD_TEST)
#include "../lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_DUST
#define LV_ATTRIBUTE_IMG_DUST
#endif

static const
LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_DUST
uint8_t ui_img_menu_setting_map[] = {

    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf3,0x4c,0x70,0x47,0x00,0xff,0xff,0xff,0xe8,
    0xff,0xff,0xff,0x82,0xff,0xff,0xff,0xe1,0xff,0xff,0xff,0xcb,0xff,0xff,0xff,0x01,
    0xff,0xff,0xff,0x39,0xff,0xff,0xff,0x98,0xff,0xff,0xff,0x29,0xff,0xff,0xff,0xad,
    0xff,0xff,0xff,0xba,0xff,0xff,0xff,0x66,0xff,0xff,0xff,0x13,0xff,0xff,0xff,0x52,

    0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,
    0x22,0x22,0x22,0x22,0x28,0x96,0xd2,0x22,0x22,0x7f,0x6b,0x82,0x27,0x22,0x22,0x22,
    0x22,0x22,0x22,0x22,0xf6,0x00,0x3d,0x72,0x22,0xf5,0x00,0x6d,0x22,0x22,0x22,0x22,
    0x22,0x22,0x22,0xe9,0x00,0x00,0x00,0xc4,0x4b,0x00,0x00,0x00,0x9e,0x22,0x22,0x22,
    0x22,0x22,0x22,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x22,0x22,0x22,
    0x22,0x22,0x22,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x22,0x22,0x22,
    0x22,0x22,0x22,0x40,0x00,0x00,0x13,0x33,0x53,0x31,0x00,0x00,0x09,0x22,0x22,0x22,
    0x22,0x22,0x77,0xd0,0x00,0x03,0x53,0x10,0x01,0x35,0x30,0x00,0x04,0x22,0x22,0x22,
    0x22,0x22,0x27,0x90,0x01,0x53,0x00,0x00,0x00,0x00,0x35,0x10,0x0b,0x22,0x22,0x22,
    0x22,0x22,0x2a,0x30,0x15,0x10,0x0b,0xd8,0x8d,0xb0,0x01,0x51,0x01,0xa2,0x27,0x22,
    0x22,0x22,0xe6,0x00,0x51,0x03,0xf2,0x22,0x22,0x2f,0x30,0x15,0x00,0x6a,0x22,0x27,
    0x22,0xe4,0x50,0x01,0x30,0x18,0x22,0x22,0x22,0x77,0x83,0x03,0x10,0x05,0x4e,0x22,
    0x28,0x60,0x00,0x05,0x10,0x42,0x72,0x22,0x22,0x72,0x74,0x01,0x30,0x00,0x06,0xa2,
    0x2b,0x00,0x00,0x13,0x01,0xa2,0x72,0x22,0x22,0x22,0x2a,0x30,0x51,0x00,0x00,0x42,
    0x26,0x00,0x00,0x13,0x0c,0x22,0x72,0x22,0x22,0x22,0x22,0xc0,0x31,0x00,0x00,0x92,
    0x26,0x00,0x00,0x13,0x0b,0x22,0x72,0x22,0x22,0x22,0x27,0xb0,0x31,0x00,0x00,0x42,
    0x26,0x00,0x00,0x13,0x0c,0x22,0x72,0x22,0x22,0x22,0x22,0xc0,0x31,0x00,0x00,0x42,
    0x2c,0x00,0x00,0x13,0x03,0xa2,0x72,0x22,0x22,0x22,0x2a,0x30,0x31,0x00,0x00,0x42,
    0x2f,0x50,0x00,0x05,0x10,0x42,0x22,0x22,0x22,0x72,0x24,0x01,0x50,0x00,0x05,0x82,
    0x22,0xa9,0x10,0x01,0x30,0x18,0x22,0x22,0x22,0x22,0x81,0x03,0x10,0x01,0x9a,0x22,
    0x22,0x22,0xa6,0x00,0x51,0x03,0xf2,0x22,0x22,0x2f,0x30,0x15,0x00,0x58,0x27,0x27,
    0x22,0x22,0x7a,0x30,0x15,0x10,0x0b,0xd8,0x8d,0xb0,0x01,0x51,0x00,0x82,0x22,0x22,
    0x22,0x22,0x77,0x90,0x01,0x53,0x00,0x00,0x00,0x00,0x35,0x10,0x0b,0x27,0x22,0x22,
    0x22,0x22,0x22,0x40,0x00,0x03,0x53,0x10,0x01,0x35,0x30,0x00,0x04,0x22,0x22,0x22,
    0x22,0x22,0x72,0x40,0x00,0x00,0x13,0x35,0x53,0x31,0x00,0x00,0x04,0x22,0x22,0x22,
    0x22,0x22,0x22,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x72,0x22,0x22,
    0x22,0x22,0x22,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x22,0x22,0x22,
    0x22,0x22,0x22,0xeb,0x00,0x00,0x00,0x64,0x46,0x00,0x00,0x00,0xce,0x22,0x22,0x22,
    0x22,0x22,0x22,0x22,0xd5,0x00,0x0d,0xe2,0x7e,0xd1,0x00,0x54,0x72,0x22,0x22,0x22,
    0x22,0x22,0x22,0x27,0x78,0xc6,0x42,0x22,0x22,0x24,0x6c,0xf2,0x27,0x22,0x22,0x22,
    0x22,0x22,0x22,0x22,0x77,0x72,0x72,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,

};

const lv_image_dsc_t ui_img_menu_setting = {
  .header.magic = LV_IMAGE_HEADER_MAGIC,
  .header.cf = LV_COLOR_FORMAT_I4,
  .header.flags = 0,
  .header.w = 32,
  .header.h = 31,
  .header.stride = 16,
  .data_size = sizeof(ui_img_menu_setting_map),
  .data = ui_img_menu_setting_map,
};

