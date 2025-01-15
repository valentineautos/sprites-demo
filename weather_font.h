/*******************************************************************************
 * Size: 60 px
 * Bpp: 1
 * Opts: --bpp 1 --size 60 --no-compress --font artillweathericons (1).ttf --symbols A --format lvgl -o weather_font.c
 ******************************************************************************/

#ifndef WEATHER_FONT
#define WEATHER_FONT 1
#endif

#if WEATHER_FONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap_wi[] = {
    /* U+0041 "A" */
    0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0,
    0x1, 0xc0, 0x0, 0x0, 0x0, 0x0, 0xe, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0,
    0x0, 0x3, 0x80, 0x0, 0x0, 0x1, 0xc0, 0x1c,
    0x1, 0x80, 0x0, 0xf, 0x0, 0x0, 0x1c, 0x0,
    0x0, 0x38, 0x0, 0x1, 0xe0, 0x0, 0x0, 0x80,
    0x0, 0x1e, 0x0, 0x0, 0x0, 0x7, 0xe0, 0xe0,
    0x0, 0x0, 0x0, 0x7f, 0xc0, 0x0, 0x0, 0xf,
    0xef, 0xff, 0x0, 0x0, 0x1, 0xff, 0xf8, 0x7c,
    0x0, 0x0, 0x1f, 0xff, 0x80, 0xf0, 0x0, 0x1,
    0xf0, 0x7c, 0x3, 0x80, 0x0, 0x1e, 0x0, 0xf0,
    0x1e, 0x0, 0x1, 0xe0, 0x3, 0x80, 0x70, 0x0,
    0xe, 0x0, 0x1e, 0x3, 0x8f, 0xc0, 0xf0, 0x0,
    0x70, 0x1c, 0x7e, 0x1f, 0x0, 0x3, 0xf0, 0xe3,
    0xf1, 0xf8, 0x0, 0x1f, 0xe7, 0x0, 0x1f, 0x80,
    0x0, 0x7f, 0xf0, 0x1, 0xe0, 0x0, 0x0, 0x1f,
    0x80, 0xe, 0x0, 0x0, 0x0, 0x78, 0x0, 0xe0,
    0x0, 0x0, 0x1, 0xc0, 0x7, 0x0, 0x0, 0x0,
    0x7, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x1,
    0xc0, 0x0, 0x0, 0x1, 0xc8, 0xe, 0x0, 0x0,
    0x0, 0xe, 0xf0, 0x78, 0x0, 0x0, 0x0, 0xf3,
    0x81, 0xe0, 0x0, 0x0, 0xf, 0xc, 0xf, 0x80,
    0x0, 0x0, 0xf8, 0x0, 0x3f, 0xff, 0xff, 0xff,
    0x80, 0x0, 0xff, 0xff, 0xff, 0xf8, 0x0, 0x1,
    0xff, 0xff, 0xff, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc_wi[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 815, .box_w = 45, .box_h = 35, .ofs_x = 3, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps_wi[] =
{
    {
        .range_start = 65, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache_wi;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc_wi = {
#else
static lv_font_fmt_txt_dsc_t font_dsc_wi = {
#endif
    .glyph_bitmap = glyph_bitmap_wi,
    .glyph_dsc = glyph_dsc_wi,
    .cmaps = cmaps_wi,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache_wi
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t weather_font = {
#else
lv_font_t weather_font = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 35,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -7,
    .underline_thickness = 3,
#endif
    .dsc = &font_dsc_wi,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if WEATHER_FONT*/

