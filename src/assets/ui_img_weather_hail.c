#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_UI_IMG_WEATHER_HAIL
#define LV_ATTRIBUTE_IMG_UI_IMG_WEATHER_HAIL
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_UI_IMG_WEATHER_HAIL uint8_t ui_img_weather_hail_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0xfb, 0xfb, 0xfb, 0xfd, 	/*Color of index 1*/
  0xd9, 0xf4, 0xfa, 0x57, 	/*Color of index 2*/
  0x4d, 0xdc, 0xfe, 0xf4, 	/*Color of index 3*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x55, 0x5a, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x95, 0x55, 0x55, 0x60, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x09, 0x55, 0x55, 0x55, 0x58, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x25, 0x55, 0x55, 0x55, 0x55, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x95, 0x55, 0x55, 0x55, 0x55, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x95, 0x55, 0x55, 0x55, 0x55, 0x60, 0x00, 0x00, 
  0x00, 0x00, 0x02, 0xaa, 0x55, 0x55, 0x55, 0x55, 0x55, 0x58, 0x00, 0x00, 
  0x00, 0x00, 0xa5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x58, 0x00, 0x00, 
  0x00, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x54, 0x00, 0x00, 
  0x00, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x80, 0x00, 
  0x00, 0x95, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x68, 0x00, 
  0x02, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x56, 0x00, 
  0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x80, 
  0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x60, 
  0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x60, 
  0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x58, 
  0x15, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x58, 
  0x15, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x54, 
  0x95, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x54, 
  0x95, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x56, 
  0x95, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x56, 
  0x15, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x56, 
  0x15, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x54, 
  0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x54, 
  0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x58, 
  0x05, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x58, 
  0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x60, 
  0x02, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x60, 
  0x00, 0x95, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x80, 
  0x00, 0x15, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x56, 0x00, 
  0x00, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x68, 0x00, 
  0x00, 0x02, 0x95, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0x80, 0x00, 
  0x00, 0x00, 0x0a, 0xaa, 0xaa, 0xab, 0xfa, 0xaa, 0xaa, 0xa8, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x26, 0x98, 0x00, 0x2f, 0xe0, 0x00, 0xa8, 0x98, 0x00, 0x00, 
  0x00, 0x00, 0x16, 0x58, 0x00, 0x3f, 0xc0, 0x00, 0x96, 0x58, 0x00, 0x00, 
  0x00, 0x00, 0x15, 0x58, 0x00, 0xbf, 0x80, 0x00, 0x95, 0x58, 0x00, 0x00, 
  0x00, 0x02, 0x95, 0x56, 0x82, 0xfe, 0xaa, 0x01, 0x95, 0x56, 0x00, 0x00, 
  0x00, 0x01, 0x55, 0x55, 0x82, 0xff, 0xff, 0x81, 0x55, 0x55, 0x00, 0x00, 
  0x00, 0x02, 0x95, 0x5a, 0x03, 0xff, 0xff, 0x82, 0x95, 0x5a, 0x00, 0x00, 
  0x00, 0x00, 0x15, 0x58, 0x02, 0xaa, 0xff, 0x80, 0x95, 0x58, 0x00, 0x00, 
  0x00, 0x00, 0x16, 0x58, 0x00, 0x00, 0xfe, 0x00, 0x96, 0x58, 0x00, 0x00, 
  0x00, 0x00, 0x28, 0xa8, 0x00, 0x02, 0xfe, 0x00, 0x28, 0xa0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t ui_img_weather_hail = {
  .header.cf = LV_IMG_CF_INDEXED_2BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 592,
  .data = ui_img_weather_hail_map,
};
