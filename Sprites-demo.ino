#include <Arduino.h>
#include <ESP_Panel_Library.h>
#include <lvgl.h>
#include "lvgl_port_v8.h"
#include "font_awesome_icons.h"
#include "weather_font.h"
#include "face_small.h"

// Global components
lv_obj_t *scr; // Screen background

// Global styles
static lv_style_t fa_icon_style;
static lv_style_t weather_icon_style;

// Icons
#define ICON_FUEL "\xEF\x94\xAF"
#define ICON_ENGINE "\xEF\x97\xB2"
#define ICON_WEATHER "A"

lv_obj_t *icon_fuel;
lv_obj_t *icon_engine;
lv_obj_t *icon_weather;
lv_obj_t *icon_face;

// Color palette
lv_color_t palette_amber = LV_COLOR_MAKE(250, 140, 0);
lv_color_t palette_black = LV_COLOR_MAKE(0, 0, 0);
lv_color_t palette_red = LV_COLOR_MAKE(255, 0, 0);
lv_color_t palette_white = LV_COLOR_MAKE(255, 255, 255);
lv_color_t palette_grey = LV_COLOR_MAKE(90, 90, 90);
lv_color_t palette_dark_grey = LV_COLOR_MAKE(60, 60, 60);

// Icon States

const uint8_t STATE_DISABLED = 0;
const uint8_t STATE_NORMAL = 1;
const uint8_t STATE_ALERT = 2;
const uint8_t STATE_WARNING = 3;

// Attributes
hw_timer_t* timer = nullptr;
unsigned long previous_ticks = 0;
const int stepper_time = 30; 

uint32_t last_update_time = 0;
const uint32_t TIMEOUT_MS = 5000;

// Styles
void make_styles(void) {
  lv_style_init(&fa_icon_style);
  lv_style_set_text_font(&fa_icon_style, &font_awesome_icons);
  lv_style_set_text_color(&fa_icon_style, palette_white);

  lv_style_init(&weather_icon_style);
  lv_style_set_text_font(&weather_icon_style, &weather_font);
  lv_style_set_text_color(&weather_icon_style, palette_white);
}

void set_state(lv_obj_t *obj, int state) {
  switch (state) {
    case STATE_DISABLED: 
      lv_obj_set_style_text_color(obj, palette_dark_grey, 0);
      break;
    case STATE_NORMAL: 
      lv_obj_set_style_text_color(obj, palette_white, 0);
      break;
    case STATE_ALERT: 
      lv_obj_set_style_text_color(obj, palette_amber, 0);
      break;
    case STATE_WARNING:
      lv_obj_set_style_text_color(obj, palette_red, 0);
      break;
  }
}

// Icons 
void make_icons(void) {
  icon_fuel = lv_label_create(scr);
  lv_label_set_text(icon_fuel, ICON_FUEL);
  lv_obj_add_style(icon_fuel, &fa_icon_style, 0);
  lv_obj_align(icon_fuel, LV_ALIGN_CENTER, 160, 0);

  icon_engine = lv_label_create(scr);
  lv_label_set_text(icon_engine, ICON_ENGINE);
  lv_obj_add_style(icon_engine, &fa_icon_style, 0);
  lv_obj_align(icon_engine, LV_ALIGN_CENTER, -160, 0);

  icon_weather = lv_label_create(scr);
  lv_label_set_text(icon_weather, ICON_WEATHER);
  lv_obj_add_style(icon_weather, &weather_icon_style, 0);
  lv_obj_align(icon_weather, LV_ALIGN_CENTER, 0, 100);

  icon_face = lv_img_create(scr);
  lv_img_set_src(icon_face, &face_small);
  lv_obj_set_style_img_recolor(icon_face, palette_white, 0);
  lv_obj_set_style_img_recolor_opa(icon_face, LV_OPA_COVER, 0);
  lv_obj_align(icon_face, LV_ALIGN_CENTER, 0, -100);
}

void scr_init() {
    ESP_Panel *panel = new ESP_Panel();
    panel->init();

    #if LVGL_PORT_AVOID_TEAR
        // When avoid tearing function is enabled, configure the RGB bus according to the LVGL configuration
        ESP_PanelBus_RGB *rgb_bus = static_cast<ESP_PanelBus_RGB *>(panel->getLcd()->getBus());
        rgb_bus->configRgbFrameBufferNumber(LVGL_PORT_DISP_BUFFER_NUM);
        rgb_bus->configRgbBounceBufferSize(LVGL_PORT_RGB_BOUNCE_BUFFER_SIZE);
    #endif
    panel->begin();

    lvgl_port_init(panel->getLcd(), panel->getTouch());
}

void IRAM_ATTR onTimer() {
    lv_tick_inc(1); // Increment LVGL's tick by 1ms
}

void setup()
{
  Serial.begin(115200);

  scr_init();

  scr = lv_scr_act();    
  lv_obj_set_style_bg_color(scr, palette_black, 0);

  // // Common styles
  make_styles();

  // // stuff
  make_icons();

  // Setup the timer
  const uint32_t lv_tick_frequency = 1000; // 1 kHz = 1ms period

  timer = timerBegin(lv_tick_frequency); // Configure the timer with 1kHz frequency
  if (!timer) {
      Serial.println("Failed to configure timer!");
      while (1); // Halt execution on failure
  }

  timerAttachInterrupt(timer, &onTimer); // Attach the ISR to the timer
  Serial.println("Timer initialized for LVGL tick!");

  last_update_time = lv_tick_get();

  set_state(icon_engine, STATE_ALERT);
  set_state(icon_fuel, STATE_WARNING);
  set_state(icon_weather, STATE_DISABLED);
}

void loop(){
    lv_timer_handler();
}