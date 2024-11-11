#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Adafruit_PCD8544.h>
#include "_constants.h"
#include "esp_adc_cal.h"

extern Adafruit_PCD8544 display;

#include "Nokia5110DisplayManager.h"

// Extern declarations for global variables
extern esp_adc_cal_characteristics_t adc_chars;
extern TaskHandle_t task_menu;
extern TaskHandle_t task_adc;
extern float v_div;
extern float s_div;
extern float offset;
extern float toffset;
extern uint8_t current_filter;
extern bool stop;
extern bool auto_scale;
extern bool menu;
extern bool info;
extern bool single_trigger;
extern uint8_t digital_wave_option;
extern uint16_t i2s_buff[BUFF_SIZE];
extern Nokia5110DisplayManager spr;
extern int btnok, btnpl, btnmn, btnbk;
extern int8_t volts_index;
extern int8_t tscale_index;
extern uint8_t opt;
extern bool set_value;
extern bool full_pix;
extern bool stop_change;
extern bool updating_screen;
extern bool new_data;
extern bool menu_action;

extern void peak_mean(uint16_t *i2s_buffer, uint32_t len, float *max_value, float *min_value, float *pt_mean);

extern bool digital_analog(uint16_t *i2s_buffer, uint32_t max_v, uint32_t min_v);

extern void trigger_freq_analog(uint16_t *i2s_buffer,
                                float sample_rate,
                                float mean,
                                uint32_t max_v,
                                uint32_t min_v,
                                float *pt_freq,
                                float *pt_period,
                                uint32_t *pt_trigger0,
                                uint32_t *pt_trigger1);

extern void trigger_freq_digital(uint16_t *i2s_buffer,
                                 float sample_rate,
                                 float mean,
                                 uint32_t max_v,
                                 uint32_t min_v,
                                 float *pt_freq,
                                 float *pt_period,
                                 uint32_t *pt_trigger0);

extern void update_screen(uint16_t *i2s_buff, float sample_rate);

extern int data[LCD_WIDTH];
#endif // GLOBALS_H