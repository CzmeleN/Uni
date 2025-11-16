#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <stdint.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define MAX8 255
#define MAX_REM 237

const uint8_t sinus[256] PROGMEM = {
    0, 3, 6, 9, 12, 15, 18, 21, 24, 28, 31, 34, 37, 40, 43, 46,
    49, 52, 55, 58, 61, 64, 67, 70, 73, 76, 79, 82, 85, 88, 91, 94,
    97, 100, 103, 106, 109, 112, 115, 118, 121, 124, 127, 130, 133, 136, 139, 141,
    144, 147, 150, 153, 155, 158, 161, 164, 166, 169, 172, 174, 177, 180, 182, 185,
    187, 190, 192, 195, 197, 200, 202, 204, 207, 209, 211, 214, 216, 218, 220, 222,
    224, 226, 228, 230, 232, 234, 236, 237, 239, 241, 242, 244, 245, 246, 248, 249,
    250, 251, 252, 253, 253, 254, 254, 255, 255, 255, 255, 254, 254, 253, 253, 252,
    251, 250, 249, 248, 246, 245, 244, 242, 241, 239, 237, 236, 234, 232, 230, 228,
    226, 224, 222, 220, 218, 216, 214, 211, 209, 207, 204, 202, 200, 197, 195, 192,
    190, 187, 185, 182, 180, 177, 174, 172, 169, 166, 164, 161, 158, 155, 153, 150,
    147, 144, 141, 139, 136, 133, 130, 127, 124, 121, 118, 115, 112, 109, 106, 103,
    100, 97, 94, 91, 88, 85, 82, 79, 76, 73, 70, 67, 64, 61, 58, 55,
    52, 49, 46, 43, 40, 37, 34, 31, 28, 24, 21, 18, 15, 12, 9, 6,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color_t;

void hsv_to_rgb(uint16_t h, uint8_t v, rgb_color_t* rgb) {
    uint8_t region = h / 60;
    uint8_t remainder = (h - region * 60) * 4; // 0-236

    uint8_t c = ((uint32_t)v * (MAX8 - (MAX8 * remainder) / MAX_REM)) / MAX8;
    uint8_t b = ((uint32_t)v * (MAX8 - (MAX8 * (MAX_REM - remainder)) / MAX_REM)) / MAX8;
    uint8_t a = 0;

    switch (region) {
        case 0: // czerwony -> zółty (+ zielony)
            rgb->r = v;
            rgb->g = b;
            rgb->b = a;
            break;
        case 1: // zółty -> zielony (- czerwony)
            rgb->r = c;
            rgb->g = v;
            rgb->b = a;
            break;
        case 2: // zielony -> cyjan (+ niebieski)
            rgb->r = a;
            rgb->g = v;
            rgb->b = b;
            break;
        case 3: // cyjan -> niebieski (- zielony)
            rgb->r = a;
            rgb->g = c;
            rgb->b = v;
            break;
        case 4: // niebieski -> magenta (+ czerwony)
            rgb->r = b; 
            rgb->g = a;
            rgb->b = v;
            break;
        default: // magenta -> czerwony (- niebieski)
            rgb->r = v;
            rgb->g = a;
            rgb->b = c;
            break;
    }
}

void timers_init()
{
    DDRB |= _BV(PB1) | _BV(PB2) | _BV(PB3);

    // oba fast PWM, top MAX8 prescaler 8
    // T1 - PB1, PB2
    TCCR1A = _BV(WGM10) | _BV(COM1A1) | _BV(COM1B1); 
    TCCR1B = _BV(WGM12) | _BV(CS11); 
    // T2 - PB3
    TCCR2A = _BV(WGM20) | _BV(WGM21) | _BV(COM2A1);
    TCCR2B = _BV(CS21);
}

int main() {
    srand(67); 

    timers_init();

    uint16_t step_id = 0;
    uint16_t hue = 0;
    rgb_color_t color;

    while(1) {
        if (step_id == 0) {
            hue = rand() % 360;
        }

        uint8_t value = pgm_read_byte(&sinus[step_id]);

        hsv_to_rgb(hue, value, &color);

        // PB1, 2, 3
        OCR1A = MAX8 - color.r;
        OCR1B = MAX8 - color.g;
        OCR2A = MAX8 - color.b;

        if (++step_id > MAX8) {
            step_id = 0;
        }

        _delay_ms(20); 
    }
}
