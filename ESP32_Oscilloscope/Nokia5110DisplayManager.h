#ifndef NOKIA5110SPRITE_H
#define NOKIA5110SPRITE_H

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Arduino.h>
#include "_constants.h"

struct Nokia5110DisplayManager; //we need to declare first to make sure class name is recognizable in globals.h
#include "globals.h"

struct Nokia5110DisplayManager {
/*
    Nokia5110DisplayManager()
    {
        display.begin();
        display.setContrast(50);
        display.clearDisplay();
        display.display();
    }

    void draw_pixel(int x, int y, bool color)
    {
        display.drawPixel(x, y, color);
    }

    void draw_line(int x0, int y0, int x1, int y1, bool color)
    {
        display.drawLine(x0, y0, x1, y1, color);
    }

    void draw_rect(int x, int y, int w, int h, bool color)
    {
        display.drawRect(x, y, w, h, color);
    }

    void fill_rect(int x, int y, int w, int h, bool color)
    {
        display.fillRect(x, y, w, h, color);
    }

    void draw_circle(int x0, int y0, int r, bool color)
    {
        display.drawCircle(x0, y0, r, color);
    }

    void fill_circle(int x0, int y0, int r, bool color)
    {
        display.fillCircle(x0, y0, r, color);
    }

    void draw_sprite(int x, int y, const uint8_t *sprite, int width, int height, bool color)
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                if (sprite[j * width + i] == 1)
                {
                    draw_pixel(x + i, y + j, color);
                }
            }
        }
    }

    void push_sprite()
    {
        display.display();
    }
    void push_sprite(Adafruit_PCD8544 *lcd){
        lcd->display();
    }

    void clear_sprite()
    {
        display.clearDisplay();
        push_sprite();
    }

    void draw_char(int x, int y, char c, bool color)
    {
        display.drawChar(x, y, c, color, !color, 1);
    }
    void draw_char(int x, int y, char c, bool color, bool bg)
    {
        display.drawChar(x, y, c, color, bg, 1);
    }
    void draw_char_no_bg(int x, int y, char c, bool color)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (pgm_read_byte(&ASCII[c - 0x20][i]) & (1 << j))
                {
                    draw_pixel(x + i, y + j, color);
                }
            }
        }
    }

    void draw_text(int x, int y, const char *text, bool color)
    {
        int offset = 0;
        while (*text)
        {
            draw_char(x + offset, y, *text, color);
            text++;
            offset += 6;
        }
    }

    void draw_text(int x, int y, const String &text, bool color)
    {
        draw_text(x, y, text.c_str(), color);
    }

    void draw_text(int x, int y, int number, bool color)
    {
        char buffer[10];
        itoa(number, buffer, 10);
        draw_text(x, y, buffer, color);
    }

    void draw_text(int x, int y, float number, bool color)
    {
        char buffer[10];
        dtostrf(number, 5, 2, buffer);
        draw_text(x, y, buffer, color);
    }

    void draw_text(int x, int y, double number, bool color)
    {
        char buffer[10];
        dtostrf(number, 5, 2, buffer);
        draw_text(x, y, buffer, color);
    }*/

    Nokia5110DisplayManager();

    void draw_pixel(int x, int y, bool color);

    void draw_line(int x0, int y0, int x1, int y1, bool color);

    void draw_rect(int x, int y, int w, int h, bool color);

    void fill_rect(int x, int y, int w, int h, bool color);

    void draw_circle(int x0, int y0, int r, bool color);

    void fill_circle(int x0, int y0, int r, bool color);

    void draw_sprite(int x, int y, const uint8_t *sprite, int width, int height, bool color);

    void push_sprite();

    void push_sprite(Adafruit_PCD8544 *lcd);

    void clear_sprite();

    void draw_char(int x, int y, char c, bool color);

    void draw_char(int x, int y, char c, bool color, bool bg);

    void draw_char_no_bg(int x, int y, char c, bool color);

    void draw_text(int x, int y, const char *text, bool color);

    void draw_text(int x, int y, const String &text, bool color);

    void draw_text(int x, int y, int number, bool color);

    void draw_text(int x, int y, float number, bool color);

    void draw_text(int x, int y, double number, bool color);
};

#endif // NOKIA5110SPRITE_H