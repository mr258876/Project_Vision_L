/*******************************************************************************
 * Size: 24 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#include "lvgl.h"

#ifndef UI_FONT_FONTAWESOMEICON24
#define UI_FONT_FONTAWESOMEICON24 1
#endif

#if UI_FONT_FONTAWESOMEICON24

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+F00D "" */
    0x1, 0x41, 0x0, 0xfe, 0x33, 0x0, 0x7, 0x2f,
    0x8, 0x3, 0xe7, 0xcc, 0x38, 0x69, 0x1, 0x61,
    0x0, 0x74, 0x40, 0x1, 0x8, 0x40, 0x10, 0xe1,
    0x0, 0x50, 0xe0, 0x18, 0xa8, 0x3, 0xe, 0x10,
    0x43, 0x80, 0x64, 0x64, 0xb0, 0xc, 0x39, 0x2e,
    0x1, 0x92, 0xc0, 0x9, 0x60, 0x18, 0x58, 0x3,
    0x25, 0x80, 0x64, 0xb0, 0xf, 0xc9, 0x60, 0x1e,
    0x4b, 0x0, 0xf1, 0xd8, 0x7, 0xec, 0x0, 0xf1,
    0x10, 0x3, 0xe8, 0x70, 0xf, 0xe, 0x10, 0x7,
    0x43, 0x80, 0x7e, 0x1c, 0x20, 0xa, 0x1c, 0x3,
    0x25, 0x0, 0x61, 0xc2, 0x7, 0x70, 0x6, 0x4b,
    0x5b, 0x0, 0xc3, 0x83, 0x0, 0x19, 0x2c, 0x0,
    0x96, 0x1, 0x85, 0x94, 0x2, 0x4b, 0x0, 0xc9,
    0x60, 0x19, 0x29, 0x1, 0x2c, 0x3, 0xc9, 0x60,
    0xb, 0x30, 0xbe, 0xb0, 0xf, 0xc9, 0xfe, 0x40
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 264, .box_w = 17, .box_h = 18, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 61453, .range_length = 1, .glyph_id_start = 1,
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
const lv_font_t ui_font_FontAwesomeIcon24 = {
#else
lv_font_t ui_font_FontAwesomeIcon24 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -9,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_FONTAWESOMEICON24*/

