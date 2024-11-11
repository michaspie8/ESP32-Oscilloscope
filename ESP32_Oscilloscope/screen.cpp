#include "screen.h"

float to_scale(float reading) {
    float temp = LCD_WIDTH -
                 ((((float) ((reading - 20480.0) / 4095.0) + (offset / 3.3)) * 3300 / (v_div * 6))) * (LCD_WIDTH - 1) -
                 1;
    return temp;
}

float to_voltage(float reading) {
    return (reading - 20480.0) / 4095.0 * 3.3;
}

uint32_t from_voltage(float voltage) {
    return uint32_t(voltage / 3.3 * 4095 + 20480.0);
}

void update_screen(uint16_t *i2s_buff, float sample_rate) {
    float mean = 0;
    float max_v, min_v;

    peak_mean(i2s_buff, BUFF_SIZE, &max_v, &min_v, &mean);

    float freq = 0;
    float period = 0;
    uint32_t trigger0 = 0;
    uint32_t trigger1 = 0;

// if analog mode OR auto mode and wave recognized as analog
    bool digital_data = false;
    if (digital_wave_option == 1) {
        trigger_freq_analog(i2s_buff, sample_rate, mean, max_v, min_v, &freq, &period, &trigger0, &trigger1);
    } else if (digital_wave_option == 0) {
        digital_data = digital_analog(i2s_buff, max_v, min_v);
        if (!digital_data) {
            trigger_freq_analog(i2s_buff, sample_rate, mean, max_v, min_v, &freq, &period, &trigger0, &trigger1);
        } else {
            trigger_freq_digital(i2s_buff, sample_rate, mean, max_v, min_v, &freq, &period, &trigger0);
        }
    } else {
        trigger_freq_digital(i2s_buff, sample_rate, mean, max_v, min_v, &freq, &period, &trigger0);
    }

    draw_sprite(freq, period, mean, max_v, min_v, trigger0, sample_rate, digital_data, true);
}

void draw_sprite(float freq,
                 float period,
                 float mean,
                 float max_v,
                 float min_v,
                 uint32_t trigger,
                 float sample_rate,
                 bool digital_data,
                 bool new_data) {

    max_v = to_voltage(max_v);
    min_v = to_voltage(min_v);

    String frequency = "";
    if (freq < 1000)
        frequency = String(freq) + "hz";
    else if (freq < 100000)
        frequency = String(freq / 1000) + "khz";
    else
        frequency = "----";

    String s_mean = "";
    if (mean > 1.0)
        s_mean = "Avg: " + String(mean) + "V";
    else
        s_mean = "Avg: " + String(mean * 1000.0) + "mV";

    String str_filter = "";
    if (current_filter == 0)
        str_filter = "None";
    else if (current_filter == 1)
        str_filter = "Pixel";
    else if (current_filter == 2)
        str_filter = "Mean-5";
    else if (current_filter == 3)
        str_filter = "Lpass9";

    String str_stop = "";
    if (!stop)
        str_stop = "RUNNING";
    else
        str_stop = "STOPPED";

    String wave_option = "";
    if (digital_wave_option == 0)
        if (digital_data)
            wave_option = "AUTO:D"; // digital data
        else
            wave_option = "AUTO:A"; // analog auto
    else if (digital_wave_option == 1)
        wave_option = "Analog"; // analog mode
    else
        wave_option = "Dig"; // digital mode

    if (new_data) {
        // Fill the whole sprite with black (Sprite is in memory so not visible yet)
        spr.clear_sprite();

        // draw_grid(); we dont use grid beacause of small screen and 1 bit color depth

        if (auto_scale) {
            auto_scale = false;
            v_div = 1000.0 * max_v / 6.0;
            s_div = period / 3.5;
            if (s_div > 7000 || s_div <= 0)
                s_div = 7000;
            if (v_div <= 0)
                v_div = 550;
        }

        // only draw digital data if a trigger was in the data
        if (!(digital_wave_option == 2 && trigger == 0))
            draw_channel1(trigger, 0, i2s_buff, sample_rate);
    }

    int shift = 150;
    if (menu) {
        //   spr.drawLine(0, 120, 280, 120, TFT_WHITE); // center line
        //   spr.fillRect(shift, 0, 102, 135, TFT_BLACK);
        //   spr.drawRect(shift, 0, 102, 135, TFT_WHITE);
        //   spr.fillRect(shift + 1, 3 + 10 * (opt - 1), 100, 11, TFT_RED);

        //   spr.drawString("AUTOSCALE", shift + 5, 5);
        //   spr.drawString(String(int(v_div)) + "mV/div", shift + 5, 15);
        //   spr.drawString(String(int(s_div)) + "uS/div", shift + 5, 25);
        //   spr.drawString("Offset: " + String(offset) + "V", shift + 5, 35);
        //   spr.drawString("T-Off: " + String((uint32_t)toffset) + "uS", shift + 5, 45);
        //   spr.drawString("Filter: " + str_filter, shift + 5, 55);
        //   spr.drawString(str_stop, shift + 5, 65);
        //   spr.drawString(wave_option, shift + 5, 75);
        //   spr.drawString("Single " + String(single_trigger ? "ON" : "OFF"), shift + 5, 85);

        //   spr.drawLine(shift, 103, shift + 100, 103, TFT_WHITE);

        //   spr.drawString("Vmax: " + String(max_v) + "V", shift + 5, 105);
        //   spr.drawString("Vmin: " + String(min_v) + "V", shift + 5, 115);
        //   spr.drawString(s_mean, shift + 5, 125);

        //   shift -= 70;

        //   // spr.fillRect(shift, 0, 70, 30, TFT_BLACK);
        //   spr.drawRect(shift, 0, 70, 30, TFT_WHITE);
        //   spr.drawString("P-P: " + String(max_v - min_v) + "V", shift + 5, 5);
        //   spr.drawString(frequency, shift + 5, 15);
        //   String offset_line = String((2.0 * v_div) / 1000.0 - offset) + "V";
        //   spr.drawString(offset_line, shift + 40, 59);

        //   if (set_value)
        //   {
        //     spr.fillRect(229, 0, 11, 11, TFT_BLUE);
        //     spr.drawRect(229, 0, 11, 11, TFT_WHITE);
        //     spr.drawLine(231, 5, 238, 5, TFT_WHITE);
        //     spr.drawLine(234, 2, 234, 8, TFT_WHITE);

        //     spr.fillRect(229, 124, 11, 11, TFT_BLUE);
        //     spr.drawRect(229, 124, 11, 11, TFT_WHITE);
        //     spr.drawLine(231, 129, 238, 129, TFT_WHITE);
        //   }

        // here we are changing the macanism. One option at a time, beacause of small screen
        // opt is an enum declared in main file.
        //  also when in menu, you can see vmax, vmin and mean values
        // with 84x48, you can place 5x7 chars, so we have max 16 chars in one line
        // The strings are placed like these: 8 5x7 chars for name, next 5x7 for ": ", and 6 5x7 chars for value (float with 2 decimal places or 6 digits for int)
        // we'll fill with black rect and draw with white

        switch (opt) {
            case None:
                break;
            case Autoscale:
                spr.fill_rect(0, 0, 84, 7, false);      // fill with black
                spr.draw_text(0, 0, "AUTOSCALE", true); // draw with white
                break;
            case Vdiv:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "Vdiv: ",
                              true);  // its not 9 chars so we can write ": " as char, normally we would write it as simple dots beacause of little space
                spr.draw_text(5 * 8, 0, v_div,
                              true); // 5*8 means 8 chars width of "Vdiv:". we just follow the rules form above
                break;
            case Sdiv:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "Sdiv: ", true);
                spr.draw_text(5 * 9, 0, s_div, true);
                break;
            case Offset:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "Offset: ", true);
                spr.draw_text(5 * 9, 0, offset, true);
                break;
            case TOffset:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "TOffset:", true);
                spr.draw_text(5 * 9, 0, toffset, true);
                break;
            case Filter:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "Filter: ", true);
                spr.draw_text(5 * 9, 0, str_filter, true);
                break;
            case Stop:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "Stop: ", true);
                spr.draw_text(5 * 9, 0, str_stop, true);
                break;
            case Mode:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "Mode: ", true);
                spr.draw_text(5 * 9, 0, wave_option, true);
                break;
            case Single:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "Single: ", true);
                spr.draw_text(5 * 9, 0, single_trigger ? "ON" : "OFF", true);
                break;
            case Clear:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "Clear", true);
                break;
            case Reset:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "Reset", true);
                break;
            case Probe:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "Probe", true);
                break;
            case UpdateF:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "UpdateF", true);
                break;
            case Cursor1:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "Cursor1", true);
                break;
            case Cursor2:
                spr.fill_rect(0, 0, 84, 7, false);
                spr.draw_text(0, 0, "Cursor2", true);
                break;
            default:
                break;
        }
    } else if (info) {
        // spr.drawLine(0, 120, 280, 120, TFT_WHITE); // center line
        // // spr.drawRect(shift + 10, 0, 280 - shift - 20, 30, TFT_WHITE);
        // spr.drawString("P-P: " + String(max_v - min_v) + "V", shift + 15, 5);
        // spr.drawString(frequency, shift + 15, 15);
        // spr.drawString(String(int(v_div)) + "mV/div", shift - 100, 5);
        // spr.drawString(String(int(s_div)) + "uS/div", shift - 100, 15);
        // String offset_line = String((2.0 * v_div) / 1000.0 - offset) + "V";
        // spr.drawString(offset_line, shift + 100, 112);

        // we need to change strategy too, so data we need to display are:
        //  1. frequency
        //  2. peak to peak voltage
        // we dont need hz, beacouse of small screen, so we'll just label on the paper on the left side of the screen, that we are displaying frequency
        //  if < 1000, we have we have 3 digits, one char for dot and 3 digits for decimal places
        //  if > 1000, we have 4 digits, two chars for "k" and dot, and 1 digit for decimal places

        // *nokia 5110 strategy
        spr.fill_rect(0, 0, 84, 7, false);
        // split freq into two parts, before and after dot
        int freq_int = freq;
        int freq_dec = (freq - freq_int) * 1000; // 1000 means 3 decimal places
        if (freq < 1000) {
            spr.draw_text(0, 0, freq_int, true);
            spr.draw_text(3 * 6, 0, ".", true);
            spr.draw_text(4 * 6, 0, freq_dec, true);
        } else {
            freq_int = freq / 1000;
            // check how many chars is freq_int
            int chars = 0;
            int temp = freq_int;
            while (temp > 0) {
                temp /= 10;
                chars++;
            }
            spr.draw_text(0, 0, freq_int, true);
            spr.draw_text(chars * 6, 0, "k", true);
            chars++;
            spr.draw_text(chars * 6, 0, ".", true);
            chars++;
            // now well make freq_dec as many chars long as left
            freq_dec = (freq - freq_int * 1000) * 10 * (14 - chars); // well have as many decimal places as we can fit
            spr.draw_text(chars * 6, 0, freq_dec, true);
        }
        // nokia 5110 strategy*
    }

    // push the drawed sprite to the screen
    // spr.pushSprite(0, 0);
    spr.push_sprite(&display);

    yield(); // Stop watchdog reset
}

void draw_grid() {

    // for (int i = 0; i < 28; i++)
    // {
    //   spr.drawPixel(i * 10, 40, TFT_WHITE);
    //   spr.drawPixel(i * 10, 80, TFT_WHITE);
    //   spr.drawPixel(i * 10, 120, TFT_WHITE);
    //   spr.drawPixel(i * 10, 160, TFT_WHITE);
    //   spr.drawPixel(i * 10, 200, TFT_WHITE);
    // }
    // for (int i = 0; i < 240; i += 10)
    // {
    //   for (int j = 0; j < 280; j += 40)
    //   {
    //     spr.drawPixel(j, i, TFT_WHITE);
    //   }
    // }
    // we dont draw grid, only center line, but info occupies 5 pixels on the top, so we need to draw it 5 pixels lower

    // *nokia 5110 strategy
    spr.draw_line(0, 48 / 2 - 5, 84, 48 / 2 - 5, true);
    // nokia 5110 strategy*
}


void draw_channel1(uint32_t trigger0, uint32_t trigger1, uint16_t *i2s_buff, float sample_rate) {
    // screen wave drawing
    data[0] = to_scale(i2s_buff[trigger0]);
    low_pass filter(0.99);
    mean_filter mfilter(5);
    mfilter.init(i2s_buff[trigger0]);
    filter._value = i2s_buff[trigger0];
    float data_per_pixel = (s_div / 40.0) / (sample_rate / 1000);

    //  uint32_t cursor = (trigger1-trigger0)/data_per_pixel;
    //  spr.drawLine(cursor, 0, cursor, 135, TFT_RED);

    uint32_t index_offset = (uint32_t)(toffset / data_per_pixel);
    trigger0 += index_offset;
    uint32_t old_index = trigger0;
    float n_data = 0, o_data = to_scale(i2s_buff[trigger0]);
    for (uint32_t i = 1; i < LCD_WIDTH; i++) {
        uint32_t index = trigger0 + (uint32_t)((i + 1) * data_per_pixel);
        if (index < BUFF_SIZE) {
            if (full_pix && s_div > 40 && current_filter == 0) {
                uint32_t max_val = i2s_buff[old_index];
                uint32_t min_val = i2s_buff[old_index];
                for (int j = old_index; j < index; j++) {
                    // draw lines for all this data points on pixel i
                    if (i2s_buff[j] > max_val)
                        max_val = i2s_buff[j];
                    else if (i2s_buff[j] < min_val)
                        min_val = i2s_buff[j];
                }
                // spr.drawLine(i, to_scale(min_val), i, to_scale(max_val), TFT_BLUE);
                //  *nokia 5110 strategy*
                spr.draw_line(i - 1, to_scale(min_val), i, to_scale(max_val), true);
            } else {
                if (current_filter == 2)
                    n_data = to_scale(mfilter.filter((float) i2s_buff[index]));
                else if (current_filter == 3)
                    n_data = to_scale(filter.filter((float) i2s_buff[index]));
                else
                    n_data = to_scale(i2s_buff[index]);

                // spr.drawLine(i - 1, o_data, i, n_data, TFT_BLUE);
                // *nokia 5110 strategy*
                spr.draw_line(i - 1, o_data, i, n_data, true);
                o_data = n_data;
            }
        } else {
            break;
        }
        old_index = index;
    }
}