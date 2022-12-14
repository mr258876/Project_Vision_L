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

#ifndef LV_ATTRIBUTE_IMG_UI_IMG_ICON_ELEMENT
#define LV_ATTRIBUTE_IMG_UI_IMG_ICON_ELEMENT
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_UI_IMG_ICON_ELEMENT uint8_t ui_img_icon_element_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0xff, 0xff, 0xff, 0x01, 	/*Color of index 1*/
  0xff, 0xff, 0xff, 0x84, 	/*Color of index 2*/
  0xff, 0xff, 0xff, 0x34, 	/*Color of index 3*/
  0xff, 0xff, 0xff, 0xda, 	/*Color of index 4*/
  0xff, 0xff, 0xff, 0xab, 	/*Color of index 5*/
  0xff, 0xff, 0xff, 0x62, 	/*Color of index 6*/
  0xff, 0xff, 0xff, 0xf2, 	/*Color of index 7*/
  0xff, 0xff, 0xff, 0x11, 	/*Color of index 8*/
  0xff, 0xff, 0xff, 0xc5, 	/*Color of index 9*/
  0xff, 0xff, 0xff, 0x4b, 	/*Color of index 10*/
  0xff, 0xff, 0xff, 0x23, 	/*Color of index 11*/
  0xff, 0xff, 0xff, 0x76, 	/*Color of index 12*/
  0xff, 0xff, 0xff, 0xea, 	/*Color of index 13*/
  0xff, 0xff, 0xff, 0x97, 	/*Color of index 14*/
  0xff, 0xff, 0xff, 0xfe, 	/*Color of index 15*/

  0x11, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x11, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x11, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x5d, 0xff, 0xf4, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x11, 0x00, 0x00, 0x00, 0x08, 0x2d, 0xff, 0xff, 0xff, 0x7d, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x11, 0x15, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x75, 0x11, 0x11, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x11, 0x2f, 0xff, 0xff, 0xd4, 0xdf, 0xff, 0xf7, 0x21, 0x11, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x13, 0x4f, 0xff, 0x4c, 0xb8, 0xb6, 0x4f, 0xff, 0x43, 0x11, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1e, 0xf7, 0xf4, 0xa8, 0x11, 0x18, 0xa4, 0xff, 0x72, 0x11, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x19, 0xff, 0xfc, 0x11, 0x00, 0x00, 0x1c, 0xff, 0xf9, 0x11, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xb4, 0xff, 0xda, 0x11, 0x00, 0x00, 0x1a, 0x7f, 0xf9, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xb2, 0xcc, 0xcb, 0x11, 0x00, 0x00, 0x13, 0x4f, 0xf9, 0x81, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x18, 0xbb, 0x81, 0x11, 0x00, 0x00, 0x1a, 0xff, 0xfe, 0x11, 0x00, 0x00, 0x00, 
  0x00, 0x11, 0x1b, 0xae, 0x99, 0x5c, 0xb1, 0x00, 0x08, 0x69, 0xff, 0xfe, 0x88, 0x11, 0x11, 0x00, 
  0x00, 0x18, 0xc9, 0xff, 0xff, 0xff, 0x42, 0x80, 0xb5, 0xdf, 0xff, 0x76, 0x1e, 0xc8, 0x11, 0x00, 
  0x00, 0x8e, 0xff, 0xff, 0xff, 0xff, 0xff, 0x53, 0x85, 0xff, 0xff, 0x98, 0x6f, 0x7e, 0x81, 0x00, 
  0x01, 0xef, 0xff, 0xff, 0x44, 0xff, 0xff, 0xfd, 0x33, 0x4f, 0xfd, 0xa8, 0x4f, 0xff, 0x21, 0x00, 
  0x0a, 0x7f, 0xff, 0x4c, 0xbb, 0x65, 0xff, 0xff, 0xe8, 0x2f, 0x9b, 0x1a, 0x4f, 0xff, 0x73, 0x11, 
  0x05, 0xff, 0xf4, 0x61, 0x11, 0x18, 0x27, 0xff, 0x73, 0x35, 0xa1, 0x11, 0x64, 0xff, 0xf5, 0x81, 
  0x0f, 0xff, 0xf6, 0x11, 0x11, 0x11, 0x1e, 0xff, 0xfc, 0x88, 0x11, 0x11, 0x16, 0xff, 0xf7, 0xa1, 
  0x0f, 0xff, 0x48, 0x11, 0x11, 0x11, 0x16, 0xff, 0xf6, 0x11, 0x11, 0x11, 0x18, 0xdf, 0xff, 0xc1, 
  0x1f, 0xff, 0x98, 0x00, 0x00, 0x11, 0x1a, 0xff, 0xf2, 0x11, 0x11, 0x11, 0x18, 0x9f, 0xff, 0x21, 
  0x1f, 0xff, 0x98, 0x00, 0x00, 0x11, 0x16, 0xff, 0xfe, 0x11, 0x11, 0x11, 0x1b, 0x4f, 0xff, 0x21, 
  0x1f, 0xff, 0xfa, 0x00, 0x00, 0x11, 0x16, 0xff, 0xf5, 0x81, 0x11, 0x11, 0x1a, 0xff, 0xf7, 0xa1, 
  0x19, 0xff, 0xf9, 0x31, 0x00, 0x18, 0x8a, 0x7f, 0xff, 0x28, 0x11, 0x11, 0x39, 0xff, 0xf9, 0xb1, 
  0x16, 0x7f, 0xff, 0x96, 0xbb, 0x3e, 0xc8, 0x5f, 0xff, 0xfe, 0xbb, 0xb6, 0x4f, 0xff, 0x7a, 0x00, 
  0x11, 0x9f, 0xff, 0xff, 0xd4, 0xff, 0x4b, 0xa4, 0xff, 0xff, 0xf4, 0xdf, 0xff, 0xff, 0x51, 0x00, 
  0x11, 0xb9, 0xff, 0xff, 0xff, 0xff, 0xf2, 0x1a, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x81, 0x00, 
  0x11, 0x0b, 0x57, 0xff, 0xff, 0xff, 0xf4, 0xb1, 0xb9, 0xff, 0xff, 0xff, 0xf7, 0x58, 0x11, 0x00, 
  0x00, 0x00, 0x0a, 0x57, 0x7f, 0x79, 0x2b, 0x00, 0x08, 0xc4, 0x77, 0x7d, 0x5a, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x8a, 0x6c, 0x63, 0x11, 0x00, 0x00, 0x13, 0x6c, 0x6a, 0x81, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t ui_img_icon_element = {
  .header.cf = LV_IMG_CF_INDEXED_4BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 32,
  .header.h = 32,
  .data_size = 576,
  .data = ui_img_icon_element_map,
};
