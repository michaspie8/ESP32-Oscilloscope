#ifndef OPTIONS_HANDLER_H
#define OPTIONS_HANDLER_H

#include <Arduino.h>
#include "_constants.h"
#include "globals.h"
#include "Nokia5110DisplayManager.h"
#include "screen.h"



void button();

void show_menu();

void hide_all();

void hide_menu();

void menu_handler();

String strings_vdiv();

String strings_sdiv();

String strings_offset();

String strings_toffset();

String strings_freq();

String strings_peak();

String strings_vmax();

String strings_vmin();

String strings_filter();







#endif // OPTIONS_HANDLER_H