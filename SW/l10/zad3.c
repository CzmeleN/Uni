#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "hd44780.h"

#define HEATER_PIN PB5
#define HEATER_PORT PORTB
#define HEATER_DDR DDRB

#define TH 1.0f

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

// inicjalizacja ADC
void adc_init()
{
    ADMUX   = _BV(REFS0) | _BV(REFS1); // referencja 1.1V
    // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
    ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
    ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;

int uart_char_available() {
    return (UCSR0A & _BV(RXC0));
}

int main(void) {
    uart_init();
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    adc_init();
    LCD_Initialize();
    LCD_Clear();

    HEATER_DDR |= _BV(HEATER_PIN);
    HEATER_PORT &= ~_BV(HEATER_PIN);

    float target = 30.0f;
    float curr = 0.0f;
    uint8_t heating = 0;

    while(1) {
        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
        ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
        uint16_t v = ADC; // weź zmierzoną wartość (0..1023)

        curr = ((v * 1.1f) / 1024.0f - 0.5f) * 100.0f;

        if (uart_char_available()) {
            char c = UDR0;

            if (c == '+') target += 0.5f;
            else if (c == '-') target -= 0.5f;

            if (target < 10.0f) target = 10.0f;
            else if (target > 55.0f) target = 55.0f;
        }

        if (curr < (target - TH)) {
            HEATER_PORT |= _BV(HEATER_PIN);
            heating = 1;
        } else if (curr > target) {
            HEATER_PORT &= ~_BV(HEATER_PIN);
            heating = 0;
        }

        char buffer[17];

        LCD_GoTo(0, 0);
        sprintf(buffer, "target: %0.1f C", target);
        LCD_WriteText(buffer);

        LCD_GoTo(0, 1);
        sprintf(buffer, "curr: %0.1f %s", curr, heating ? "[ON] " : "[OFF]");
        LCD_WriteText(buffer);

        _delay_ms(100);
    }
}
