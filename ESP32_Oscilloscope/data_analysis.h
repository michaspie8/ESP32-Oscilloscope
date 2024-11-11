#ifndef DATA_ANALYSIS_H
#define DATA_ANALYSIS_H

#include <Arduino.h>
#include <driver/i2s.h>
#include <driver/adc.h>
#include <soc/syscon_reg.h>
#include "filters.h"
#include "_constants.h"
#include "globals.h"
#include "Nokia5110DisplayManager.h"
#include "screen.h"
#include "options_handler.h"

void peak_mean(uint16_t *i2s_buffer, uint32_t len, float *max_value, float *min_value, float *pt_mean);

bool digital_analog(uint16_t *i2s_buffer, uint32_t max_v, uint32_t min_v);

void trigger_freq_analog(uint16_t *i2s_buffer,
                         float sample_rate,
                         float mean,
                         uint32_t max_v,
                         uint32_t min_v,
                         float *pt_freq,
                         float *pt_period,
                         uint32_t *pt_trigger0,
                         uint32_t *pt_trigger1);

void trigger_freq_digital(uint16_t *i2s_buffer,
                          float sample_rate,
                          float mean,
                          uint32_t max_v,
                          uint32_t min_v,
                          float *pt_freq,
                          float *pt_period,
                          uint32_t *pt_trigger0);

#endif // DATA_ANALYSIS_H
