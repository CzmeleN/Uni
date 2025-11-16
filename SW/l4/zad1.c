#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

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

void timer1_init()
{
    // ustaw tryb licznika
    // WGM1  = 0000 -- normal
    // CS1   = 001  -- prescaler 1
    TCCR1B = _BV(CS10);
}
FILE uart_file;

int main()
{
    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    // zainicjalizuj licznik
    timer1_init();

    uint16_t start, end;

    start = TCNT1;
    end = TCNT1;

    uint16_t overhead = end - start;

    while(1) {
        volatile int8_t a8 = 63, b8 = 45, c8;

        start = TCNT1;
        c8 = a8 + b8;
        end = TCNT1;
        printf("[+ i8] %"PRIu16" cykli\r\n", end - start - overhead);

        start = TCNT1;
        c8 = a8 * b8;
        end = TCNT1;
        printf("[* i8] %"PRIu16" cykli\r\n", end - start - overhead);

        start = TCNT1;
        c8 = a8 / b8;
        end = TCNT1;
        printf("[/ i8] %"PRIu16" cykli\r\n", end - start - overhead);

        volatile int16_t a16 = 4019, b16 = 1234, c16;

        start = TCNT1;
        c16 = a16 + b16;
        end = TCNT1;
        printf("[+ i16] %"PRIu16" cykli\r\n", end - start - overhead);

        start = TCNT1;
        c16 = a16 * b16;
        end = TCNT1;
        printf("[* i16] %"PRIu16" cykli\r\n", end - start - overhead);

        start = TCNT1;
        c16 = a16 / b16;
        end = TCNT1;
        printf("[/ i16] %"PRIu16" cykli\r\n", end - start - overhead);

        volatile int32_t a32 = 1234098543, b32 = 934567823, c32;

        start = TCNT1;
        c32 = a32 + b32;
        end = TCNT1;
        printf("[+ i32] %"PRIu16" cykli\r\n", end - start - overhead);

        start = TCNT1;
        c32 = a32 * b32;
        end = TCNT1;
        printf("[* i32] %"PRIu16" cykli\r\n", end - start - overhead);

        start = TCNT1;
        c32 = a32 / b32;
        end = TCNT1;
        printf("[/ i32] %"PRIu16" cykli\r\n", end - start - overhead);

        volatile int64_t a64 = 1234098543, b64 = 934567823, c64;

        start = TCNT1;
        c64 = a64 + b64;
        end = TCNT1;
        printf("[+ i64] %"PRIu16" cykli\r\n", end - start - overhead);

        start = TCNT1;
        c64 = a64 * b64;
        end = TCNT1;
        printf("[* i64] %"PRIu16" cykli\r\n", end - start - overhead);

        start = TCNT1;
        c64 = a64 / b64;
        end = TCNT1;
        printf("[/ i64] %"PRIu16" cykli\r\n", end - start - overhead);

        volatile float af = 12948.123f, bf = 129192.1238f, cf;

        start = TCNT1;
        cf = af + bf;
        end = TCNT1;
        printf("[+ f] %"PRIu16" cykli\r\n", end - start - overhead);

        start = TCNT1;
        cf = af * bf;
        end = TCNT1;
        printf("[* f] %"PRIu16" cykli\r\n", end - start - overhead);

        start = TCNT1;
        cf = af / bf;
        end = TCNT1;
        printf("[/ f] %"PRIu16" cykli\r\n\r\n", end - start - overhead);

        _delay_ms(5000);
    }
}

