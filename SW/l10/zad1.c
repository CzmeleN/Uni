#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "hd44780.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
    // ustaw baudrate
    UBRR0 = UBRR_VALUE;
    // włącz odbiornik i nadajnik
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
    // ustaw format 8n1
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
    // czekaj aż transmiter gotowy
    while(!(UCSR0A & _BV(UDRE0)));
    UDR0 = data;
    return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
    // czekaj aż znak dostępny
    while (!(UCSR0A & _BV(RXC0)));
    return UDR0;
}

FILE uart_file;

char buff[2][16]; 
// x = 0, y = 0 - lewy górny
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

void clear_buffer() {
    memset(buff[0], ' ', 16);
    memset(buff[1], ' ', 16);

    cursor_x = 0;
    cursor_y = 0;
}

void redraw_lcd() {
    LCD_Clear();

    LCD_GoTo(0, 0);
    for(int i = 0; i < 16; i++) LCD_WriteData(buff[0][i]);

    LCD_GoTo(0, 1);
    for(int i = 0; i < 16; i++) LCD_WriteData(buff[1][i]);

    LCD_GoTo(cursor_x, cursor_y);
}

void scroll_display() {
    memcpy(buff[0], buff[1], 16);
    memset(buff[1], ' ', 16);

    cursor_y = 1;
    cursor_x = 0;

    redraw_lcd();
}

int main()
{
    uart_init();
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    LCD_Initialize();
    LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_ON | HD44780_CURSOR_BLINK);
    LCD_Clear();
    clear_buffer();

    char c;

    while(1) {
        c = getchar(); 

        if (c == '\r' || c == '\n') {
            scroll_display();
            continue;
        }

        buff[cursor_y][cursor_x] = c;

        LCD_GoTo(cursor_x, cursor_y);
        LCD_WriteData(c);

        cursor_x++;

        if (cursor_x >= 16) {
            if (cursor_y == 0) {
                cursor_y = 1;
                cursor_x = 0;
                LCD_GoTo(0, 1);
            } else {
                scroll_display();
            }
        }
    }
}
