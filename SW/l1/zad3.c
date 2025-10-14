#include <avr/io.h>
#include <util/delay.h>

const uint8_t nrs[10] = {
    0b11000000,
    0b11111001,
    0b10100100,
    0b10110000,
    0b10011001,
    0b10010010,
    0b10000010,
    0b11111000,
    0b10000000,
    0b10010000 
};

int main(void) {
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0); // disable uart

    DDRD = 0b11111111;

    while (1) {
        for (int i = 0; i < 10; i++) {
            PORTD = nrs[i];
            _delay_ms(1000);
        }
    }
}
