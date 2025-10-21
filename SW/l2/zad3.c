#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN_RESET PB1
#define BTN_PREV PB2
#define BTN_NEXT PB3
#define BTN_PIN PINB
#define BTN_PORT PORTB
#define BTN_DDR DDRB

#define DELAY 10

inline uint8_t to_gray(uint8_t n) {
    return n ^ (n >> 1);
}

int main() {
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0); // disable uart

    LED_DDR |= 0b11111111;
    BTN_PORT |= _BV(BTN_RESET) | _BV(BTN_NEXT) | _BV(BTN_PREV);

    uint8_t n = 0;
    LED_PORT = to_gray(n);

    while (1) {
        uint8_t buttons = BTN_PIN;

        if ((buttons & _BV(BTN_RESET)) == 0) {
            n = 0;
            LED_PORT = to_gray(n);
            _delay_ms(DELAY);
            while ((BTN_PIN & _BV(BTN_RESET)) == 0);
        } else if ((buttons & _BV(BTN_PREV)) == 0) {
            n--;
            LED_PORT = to_gray(n);
            _delay_ms(DELAY);
            while((BTN_PIN & _BV(BTN_PREV)) == 0);
        } else if ((buttons & _BV(BTN_NEXT)) == 0) {
            n++;
            LED_PORT = to_gray(n);
            _delay_ms(DELAY);
            while((BTN_PIN & _BV(BTN_NEXT)) == 0);
        }
    }
}
