/*******************************************************************************
 * Size: 48 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#include "lvgl.h"

#ifndef UI_FONT_FONTAWESOMEICON48
#define UI_FONT_FONTAWESOMEICON48 1
#endif

#if UI_FONT_FONTAWESOMEICON48

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+F7C2 "" */
    0x0, 0xff, 0xa3, 0xff, 0xff, 0x8f, 0x8c, 0x1,
    0xff, 0xc1, 0x87, 0x0, 0xff, 0xe3, 0x9c, 0xe0,
    0x80, 0x7f, 0xa1, 0xc0, 0x3f, 0xf9, 0x47, 0xa0,
    0x1f, 0xd0, 0xe0, 0x1f, 0xfc, 0xc3, 0x60, 0xf,
    0xa1, 0xc0, 0x3f, 0xf9, 0xd4, 0x1, 0xe8, 0x70,
    0xf, 0xfe, 0x79, 0x80, 0x74, 0x38, 0x4, 0xff,
    0xf8, 0x2, 0xff, 0xc8, 0x0, 0xbf, 0xfc, 0x1,
    0xfe, 0x87, 0x0, 0xff, 0xea, 0xc3, 0x80, 0x7f,
    0xf5, 0x61, 0xc0, 0x3f, 0xfa, 0xb0, 0xe0, 0x1f,
    0xfd, 0x58, 0x70, 0xf, 0xfe, 0xb3, 0x80, 0x7f,
    0xff, 0xc0, 0x3f, 0xfb, 0xcf, 0xff, 0x80, 0x2f,
    0xfc, 0x80, 0xb, 0xff, 0xc0, 0x1f, 0xff, 0xf0,
    0xf, 0xff, 0xf8, 0x7, 0xff, 0xfc, 0x3, 0xff,
    0xfe, 0x1, 0xff, 0xff, 0x0, 0xff, 0xff, 0x80,
    0x7f, 0xff, 0xc0, 0x3f, 0xff, 0xe0, 0x1f, 0xff,
    0xf0, 0xf, 0xff, 0xf8, 0x7, 0xff, 0xfc, 0x3,
    0xff, 0xfe, 0x1, 0xff, 0xff, 0x0, 0x8c, 0x3,
    0xff, 0xac, 0x74, 0x1, 0xff, 0xd6, 0xa6, 0x30,
    0xf, 0xfe, 0xa1, 0xb0, 0x69, 0x80, 0x7f, 0xf4,
    0x8f, 0x40, 0x3, 0x92, 0x60, 0x1f, 0xfc, 0xe3,
    0x9c, 0x10
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 576, .box_w = 36, .box_h = 48, .ofs_x = 0, .ofs_y = -6}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 63426, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 1,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t ui_font_FontAwesomeIcon48 = {
#else
lv_font_t ui_font_FontAwesomeIcon48 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 48,          /*The maximum line height required by the font*/
    .base_line = 6,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -17,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_FONTAWESOMEICON48*/

