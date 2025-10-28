#include <avr/pgmspace.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define BUZZ PB5
#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

#define TONE(step, delay) \
for (uint16_t i = 0; i < (uint32_t)1000 * (delay) / (step) / 2; i++) { \
    BUZZ_PORT |= _BV(BUZZ); \
    _delay_us(step); \
    BUZZ_PORT &= ~_BV(BUZZ); \
    _delay_us(step); \
}

enum ID { PAUSE, C, D, E, F, G, A, B };

// 262hz
#define NOTE_C 1908
// 294hz
#define NOTE_D 1701
// 330hz
#define NOTE_E 1515
// 349hz
#define NOTE_F 1433
// 392hz
#define NOTE_G 1276
// 440hz
#define NOTE_A 1136
// 494hz
#define NOTE_B 1012

#define BPM 120
#define QUARTER_MS (60000 / BPM)
#define FULL_MS (QUARTER_MS * 4)
#define HALF_MS (QUARTER_MS * 2)
#define EIGHTH_MS (QUARTER_MS / 2)
#define SIXTEENTH_MS (QUARTER_MS / 4)

typedef struct {
    uint8_t step;
    uint16_t delay;
} Note;

// 12 taktów * 3 * QUARTER + 8 taktów * 4 * QUARTER = 68 * 60000 / 120 = 34s (+ pauzy)
static const Note melody[] PROGMEM = {
    // wlazł kotek
    {G, QUARTER_MS},
    {E, QUARTER_MS},
    {E, QUARTER_MS},
    {F, QUARTER_MS},
    {D, QUARTER_MS},
    {D, QUARTER_MS},
    {C, EIGHTH_MS},
    {E, EIGHTH_MS},
    {G, HALF_MS},
    {G, QUARTER_MS},
    {E, QUARTER_MS},
    {E, QUARTER_MS},
    {F, QUARTER_MS},
    {D, QUARTER_MS},
    {D, QUARTER_MS},
    {C, EIGHTH_MS},
    {E, EIGHTH_MS},
    {C, HALF_MS},
    {G, QUARTER_MS},
    {E, QUARTER_MS},
    {E, QUARTER_MS},
    {F, QUARTER_MS},
    {D, QUARTER_MS},
    {D, QUARTER_MS},
    {C, EIGHTH_MS},
    {E, EIGHTH_MS},
    {G, HALF_MS},
    {G, EIGHTH_MS},
    {E, EIGHTH_MS},
    {E, EIGHTH_MS},
    {F, QUARTER_MS},
    {D, QUARTER_MS},
    {D, QUARTER_MS},
    {C, EIGHTH_MS},
    {E, EIGHTH_MS},
    {C, HALF_MS},
    {PAUSE, FULL_MS},
    // przybyli ułani
    {C, EIGHTH_MS},
    {C, QUARTER_MS},
    {D, EIGHTH_MS},
    {E, EIGHTH_MS},
    {E, QUARTER_MS},
    {C, EIGHTH_MS},
    {B, EIGHTH_MS},
    {C, EIGHTH_MS},
    {D, QUARTER_MS},
    {C, HALF_MS},
    {E, EIGHTH_MS},
    {E, QUARTER_MS},
    {F, EIGHTH_MS},
    {G, EIGHTH_MS},
    {G, QUARTER_MS},
    {F, EIGHTH_MS},
    {E, EIGHTH_MS},
    {F, EIGHTH_MS},
    {G, QUARTER_MS},
    {D, HALF_MS},
    {G, EIGHTH_MS},
    {G, QUARTER_MS},
    {F, EIGHTH_MS},
    {E, EIGHTH_MS},
    {E, QUARTER_MS},
    {D, EIGHTH_MS},
    {C, EIGHTH_MS},
    {C, EIGHTH_MS},
    {D, EIGHTH_MS},
    {E, EIGHTH_MS},
    {F, EIGHTH_MS},
    {F, QUARTER_MS},
    {D, EIGHTH_MS},
    {G, EIGHTH_MS},
    {G, QUARTER_MS},
    {C, EIGHTH_MS},
    {D, EIGHTH_MS},
    {C, EIGHTH_MS},
    {D, QUARTER_MS},
    {C, FULL_MS},
    {PAUSE, FULL_MS}
};

int main() {
    BUZZ_DDR |= _BV(BUZZ);

    const uint16_t notes_count = sizeof(melody) / sizeof(Note);

    while (1) {
        for (uint16_t i = 0; i < notes_count; ++i) {
            uint8_t step = pgm_read_u8(&melody[i].step);
            uint16_t delay = pgm_read_u16(&melody[i].delay);

            switch (step) {
                case C:
                    TONE(NOTE_C, delay);
                    break;
                case D:
                    TONE(NOTE_D, delay);
                    break;
                case E:
                    TONE(NOTE_E, delay);
                    break;
                case F:
                    TONE(NOTE_F, delay);
                    break;
                case G:
                    TONE(NOTE_G, delay);
                    break;
                case A:
                    TONE(NOTE_A, delay);
                    break;
                case B:
                    TONE(NOTE_B, delay);
                    break;
                default:
                    for (uint16_t j = 0; j < delay; ++j) {
                        _delay_ms(1);
                    }
                    break;
            }
        }
    }
}
