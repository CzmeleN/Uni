#include <avr/io.h>
#include <stdio.h>
#include <ctype.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define DOT_LIGHT_MS 200
#define BETWEEN_MULT 2
#define DASH_MULT 3
#define SPACE_MULT 4

const char* MORSE_ALPHA[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};

const char* MORSE_NUM[] = {
    "-----", ".----", "..---", "...--", "....-",
    ".....", "-....", "--...", "---..", "----."
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

void dot() {
    LED_PORT |= _BV(LED);
    _delay_ms(DOT_LIGHT_MS);
    LED_PORT &= ~_BV(LED);
}

void dash() {
    LED_PORT |= _BV(LED);
    _delay_ms(DASH_MULT * DOT_LIGHT_MS);
    LED_PORT &= ~_BV(LED);
}

int main()
{
    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    
    LED_DDR |= _BV(LED);

    while(1) {
        char inp = getchar();
        const char* str = NULL;

        inp = toupper(inp);

        if (inp >= 'A' && inp <= 'Z') {
            str = MORSE_ALPHA[inp - 'A'];
        } else if (inp >= '0' && inp <= '9') {
            str = MORSE_NUM[inp - '0'];
        } else if (inp == ' ') {
            _delay_ms(SPACE_MULT * DOT_LIGHT_MS);
        }

        if (str == NULL) continue;

        while (*str) {
            if (*str == '.') {
                dot();
            } else {
                dash();
            }
            _delay_ms(DOT_LIGHT_MS);
            str++;
        }

        _delay_ms(BETWEEN_MULT * DOT_LIGHT_MS);
    }
}
