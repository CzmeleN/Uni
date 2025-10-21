#include <avr/io.h>
#include <util/delay.h>

#define LED PB0
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB3
#define BTN_PIN PINB
#define BTN_PORT PORTB

#define BUFF_SIZE 256

#define STATE_SHIFT 14
#define STATE_NONE 0b00
#define STATE_UP 0b01
#define STATE_DOWN 0b11

#define DELAY_MASK 0b00111111111111
#define STATE_MASK 0b11

#define TIME_TICK_MS 10
#define RECORDING_TICKS 100

enum { IDLE, RECORDING, PLAYING };

typedef struct {
    uint16_t buff[BUFF_SIZE];
    uint16_t write_id;
    uint16_t read_id;
} ring_buff_t;

inline uint8_t get_state(uint16_t x) {
    return (x >> STATE_SHIFT) & STATE_MASK;
}

inline uint16_t get_delay(uint16_t x) {
    return x & DELAY_MASK;
}

inline uint16_t pack_item(uint8_t state, uint16_t delay) {
    return (uint16_t)state << STATE_SHIFT | delay;
}

void rb_init(ring_buff_t *rb) {
    rb->write_id = 0;
    rb->read_id = 0;
}

uint8_t rb_write(ring_buff_t *rb, uint16_t x) {
    if (((rb->write_id + 1) & (BUFF_SIZE - 1)) == rb->read_id) {
        return 1;
    }

    rb->buff[rb->write_id] = x;
    rb->write_id = (rb->write_id + 1) & (BUFF_SIZE - 1);

    return 0;
}

uint16_t rb_read(ring_buff_t *rb) {
    if (rb->write_id == rb->read_id) {
        return pack_item(STATE_NONE, 0);
    }

    uint16_t ret = rb->buff[rb->read_id];

    rb->read_id = (rb->read_id + 1) & (BUFF_SIZE - 1);

    return ret;
}

inline uint8_t get_button_state() {
    return BTN_PIN & _BV(BTN);
}

int main() {
    BTN_PORT |= _BV(BTN);
    LED_DDR |= _BV(LED);
    LED_PORT &= ~_BV(LED);

    ring_buff_t buff;
    rb_init(&buff);

    uint8_t playback_state = IDLE;
    uint8_t last_state;

    uint16_t ticks = 0;
    uint16_t state_ticks = 0;

    while (1) {
        switch (playback_state) {
            case IDLE:
                last_state = get_button_state();

                if (last_state == 0) {
                    ticks = 0;
                    state_ticks = 0;
                    playback_state = RECORDING;
                }

                break;
            case RECORDING: {
                uint8_t curr_state = get_button_state();

                if (curr_state != last_state) {
                    uint8_t new_state;

                    if (last_state == 0) {
                        new_state = STATE_DOWN;
                    } else {
                        new_state = STATE_UP;
                    }

                    rb_write(&buff, pack_item(new_state, state_ticks));
                    state_ticks = 0;
                }

                state_ticks++;
                ticks++;

                if (ticks == RECORDING_TICKS) {
                    rb_write(&buff, pack_item((last_state == 0 ? STATE_DOWN : STATE_UP), state_ticks));
                    playback_state = PLAYING;

                    break;
                }

                last_state = curr_state;
                _delay_ms(TIME_TICK_MS);

                break;
            }
            case PLAYING: {
                uint16_t curr = rb_read(&buff);
                uint8_t state = get_state(curr);

                if (state == STATE_NONE) {
                    LED_PORT &= ~_BV(LED);
                    playback_state = IDLE;

                    break;
                }

                curr = get_delay(curr);

                if (state == STATE_DOWN) {
                    LED_PORT |= _BV(LED);
                } else {
                    LED_PORT &= ~_BV(LED);
                }

                while (curr--) _delay_ms(TIME_TICK_MS);

                break;
            }
        }
    }
}
