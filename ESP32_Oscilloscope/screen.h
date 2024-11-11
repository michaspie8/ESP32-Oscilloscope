#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <algorithm>
#include <Arduino.h>
#include <SPI.h>
#include "_constants.h"
#include "filters.h"
#include "globals.h"
#include "Nokia5110DisplayManager.h"

float to_scale(float reading);

float to_voltage(float reading);

uint32_t from_voltage(float voltage);

void update_screen(uint16_t *i2s_buff, float sample_rate);

void draw_sprite(float freq,
                 float period,
                 float mean,
                 float max_v,
                 float min_v,
                 uint32_t trigger,
                 float sample_rate,
                 bool digital_data,
                 bool new_data);

void draw_grid();

void draw_channel1(uint32_t trigger0, uint32_t trigger1, uint16_t *i2s_buff, float sample_rate);

#endif // SCREEN_H