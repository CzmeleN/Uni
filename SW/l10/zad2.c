#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "hd44780.h"

// każdy znak 8 wierszy
// bity idą jak znaki
// 0x10 = 10000 - 1 zapalony od lewej
// itd..
const uint8_t custom_chars[5][8] = {
    {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C},
    {0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E},
    {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F}
};

void load_custom_characters() {
    // adres jako id * 8
    // na start adres znaku 1
    LCD_WriteCommand(HD44780_CGRAM_SET | (1 * 8));

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            LCD_WriteData(custom_chars[i][j]);
        }
    }
}

void draw_progress_bar(uint8_t progress) {
    LCD_GoTo(0, 0);

    uint8_t full = progress / 5;
    uint8_t part = progress - full * 5;

    for (uint8_t i = 0; i < 16; i++) {
        if (i < full) {
            LCD_WriteData(5); 
        } else if (i == full) {
            if (part > 0) {
                LCD_WriteData(part);
            } else {
                LCD_WriteData(' ');
            }
        } else {
            LCD_WriteData(' ');
        }
    }
}

int main(void) {
    LCD_Initialize();
    LCD_Clear();
    load_custom_characters();
    LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);

    uint8_t val = 0;

    while (1) {
        draw_progress_bar(val);

        char buffer[16];
        sprintf(buffer, "progress: %2d/80", val);
        LCD_GoTo(0, 1);
        LCD_WriteText(buffer);

        val++;
        if (val > 80) val = 0;

        _delay_ms(100);
    }
}
