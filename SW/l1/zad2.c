#include <avr/io.h>
#include <util/delay.h>

#define DELAY 100
#define START 0b11
#define END 0b11000000

int main() {
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0); // disable uart

    DDRD |= 0b11111111; // pd0 .. pd7 as out
    
    uint8_t pattern = START;

    while(1) {
        while (pattern < END) {
            PORTD = pattern;
            _delay_ms(DELAY);
            pattern <<= 1;
        }

        while (pattern > START) {
            PORTD = pattern;
            _delay_ms(DELAY);
            pattern >>= 1;
        }
    }
}
