#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define DIGIT_DDR DDRC
#define DIGIT_PORT PORTC
#define DIGIT_ONES_PIN PC1
#define DIGIT_TENS_PIN PC0

#define DELAY 5
#define SECOND 1000

#define BLANK 0b11111111

#define TENS 0
#define ONES 1

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

void select(uint8_t which) {
    DIGIT_PORT |= _BV(DIGIT_ONES_PIN) | _BV(DIGIT_TENS_PIN);

    if (which == TENS) {
        DIGIT_PORT &= ~_BV(DIGIT_TENS_PIN);
    } else {
        DIGIT_PORT &= ~_BV(DIGIT_ONES_PIN);
    }
}

int main(void) {
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0); // disable uart

    DDRD = 0b11111111;
    DIGIT_DDR |= _BV(DIGIT_TENS_PIN) | _BV(DIGIT_ONES_PIN);

    while (1) {
        for (uint8_t i = 0; i < 6; i++) {
            for (uint8_t j = 0; j < 10; ++j) {
                for (uint16_t k = 0; k < SECOND; k += 2 * DELAY) {
                    select(ONES);
                    PORTD = nrs[j];
                    _delay_ms(DELAY);

                    select(TENS);
                    PORTD = i == 0 ? BLANK : nrs[i];
                    _delay_ms(DELAY);
                }
            }
        }
    }
}
