#include "Nokia5110DisplayManager.h"

Nokia5110DisplayManager::Nokia5110DisplayManager() {
    display.begin();
    display.setContrast(50);
    display.clearDisplay();
    display.display();
}

void Nokia5110DisplayManager::draw_pixel(int x, int y, bool color) {
    display.drawPixel(x, y, color);
}

void Nokia5110DisplayManager::draw_line(int x0, int y0, int x1, int y1, bool color) {
    display.drawLine(x0, y0, x1, y1, color);
}

void Nokia5110DisplayManager::draw_rect(int x, int y, int w, int h, bool color) {
    display.drawRect(x, y, w, h, color);
}

void Nokia5110DisplayManager::fill_rect(int x, int y, int w, int h, bool color) {
    display.fillRect(x, y, w, h, color);
}

void Nokia5110DisplayManager::draw_circle(int x0, int y0, int r, bool color) {
    display.drawCircle(x0, y0, r, color);
}

void Nokia5110DisplayManager::fill_circle(int x0, int y0, int r, bool color) {
    display.fillCircle(x0, y0, r, color);
}

void Nokia5110DisplayManager::draw_sprite(int x, int y, const uint8_t *sprite, int width, int height, bool color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (sprite[j * width + i] == 1) {
                draw_pixel(x + i, y + j, color);
            }
        }
    }
}

void Nokia5110DisplayManager::push_sprite() {
    display.display();
}

void Nokia5110DisplayManager::clear_sprite() {
    display.clearDisplay();
}

void Nokia5110DisplayManager::push_sprite(Adafruit_PCD8544 *lcd){
    lcd->display();
}

void Nokia5110DisplayManager::draw_char(int x, int y, char c, bool color) {
    display.drawChar(x, y, c, color, !color, 1);
}

void Nokia5110DisplayManager::draw_char(int x, int y, char c, bool color, bool bg) {
    display.drawChar(x, y, c, color, bg, 1);
}

void Nokia5110DisplayManager::draw_char_no_bg(int x, int y, char c, bool color) {
    display.drawChar(x, y, c, color, false, 1);
}

void Nokia5110DisplayManager::draw_text(int x, int y, const char *text, bool color) {
    int offset = 0;
    while (*text) {
        draw_char(x + offset, y, *text, color);
        text++;
        offset += 6;
    }
}

void Nokia5110DisplayManager::draw_text(int x, int y, const String &text, bool color) {
    draw_text(x, y, text.c_str(), color);
}

void Nokia5110DisplayManager::draw_text(int x, int y, int number, bool color) {
    char buffer[10];
    itoa(number, buffer, 10);
    draw_text(x, y, buffer, color);
}

void Nokia5110DisplayManager::draw_text(int x, int y, float number, bool color) {
    char buffer[10];
    dtostrf(number, 5, 2, buffer);
    draw_text(x, y, buffer, color);
}

void Nokia5110DisplayManager::draw_text(int x, int y, double number, bool color) {
    char buffer[10];
    dtostrf(number, 5, 2, buffer);
    draw_text(x, y, buffer, color);
}