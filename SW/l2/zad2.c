#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define LED PB0
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB3
#define BTN_PIN PINB
#define BTN_PORT PORTB

#define BASE_TICK 10
#define DASH_TICKS (BASE_TICK * 20)
#define NEXT_TICKS (BASE_TICK * 40)
#define SPACE_TICKS (BASE_TICK * 80)

#define N 54

enum { IDLE, PRESSED, WAITING_NEXT, WAITING_SPACE };

const char MORSE_CHARS[N] = {
    0, // unused
    0, // root
    'E', // .
    'T', // -
    'I', // ..
    'A', // .-
    'N', // -.
    'M', // --
    'S', // ...
    'U', // ..-
    'R', // .-.
    'W', // .--
    'D', // -..
    'K', // -.-
    'G', // --.
    'O', // ---
    'H', // ....
    'V', // ...-
    'F', // ..-.
    0,      // ..--
    'L', // ._..
    0,
    'P', // .--.
    'J', // .---
    'B', // -...
    'X', // -..-
    'C', // -.-.
    'Y', // -.--
    'Z', // --..
    'Q', // --.-
    0,
    0,
    '5', // .....
    '4', // ....-
    0,
    '3', // ...--
    0,
    0,
    0,
    '2', // ..---
    0,
    0,
    0,
    0,
    0,
    0,
    '1', // .----
    '6', // -....
    '7', // --...
    0,
    '8', // ---..
    0,
    '9', // ----.
    '0'  // -----
};

// inicjalizacja UART
void uart_init()
{
    // ustaw baudrate
    UBRR0 = UBRR_VALUE;
    // wyczyść rejestr UCSR0A
    UCSR0A = 0;
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

inline uint8_t get_button_state() {
    return BTN_PIN & _BV(BTN);
}

inline void led_on() {
    LED_PORT |= _BV(LED);
}

inline void led_off() {
    LED_PORT &= ~_BV(LED);
}

int main() {
    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    BTN_PORT |= _BV(BTN);
    LED_DDR |= _BV(LED);
    led_off();

    uint8_t state = IDLE;
    uint8_t tree_id = 1;
    uint16_t ticks = 0;

    while (1) {
        uint8_t button_state = get_button_state();

        switch (state) {
            case IDLE:
                if (button_state == 0) {
                    state = PRESSED;
                    ticks = 0;
                    led_off();
                }
                    
                break;
            case PRESSED:
                if (button_state != 0) {
                    led_off();

                    if (ticks < DASH_TICKS) {
                        tree_id *= 2; 
                    } else {
                        tree_id = tree_id * 2 + 1;
                    }

                    if (tree_id >= N) {
                        putchar('*');
                        tree_id = 1;
                        state = IDLE;
                    } else {
                        state = WAITING_NEXT;
                        ticks = 0;
                    }
                }

                if (++ticks == DASH_TICKS) {
                    led_on();
                }

                break;
            case WAITING_NEXT:
                if (button_state == 0) {
                    state = PRESSED;
                    ticks = 0;
                } else if (ticks == NEXT_TICKS) {
                    const char res = MORSE_CHARS[tree_id];

                    if (res != 0) {
                        putchar(res);
                    } else {
                        putchar('*');
                    }

                    tree_id = 1;
                    state = WAITING_SPACE;
                }

                ticks++;

                break;
            case WAITING_SPACE:
                if (button_state == 0) {
                    state = PRESSED;
                    ticks = 0;
                } else if (ticks == SPACE_TICKS) {
                    putchar(' ');
                    state = IDLE;
                }
                
                ticks++;

                break;
        }

        _delay_ms(BASE_TICK);
    }
}
