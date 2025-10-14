#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define FMT_NL "\r\n"

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

int main()
{
    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    int8_t a8, b8;
    printf("two int8" FMT_NL);
    scanf("%" SCNd8 " %" SCNd8, &a8, &b8);
    printf("add: %" PRId8 FMT_NL, (int8_t)(a8 + b8));
    printf("mult: %" PRId8 FMT_NL, (int8_t)(a8 * b8));
    printf("div: %" PRId8 FMT_NL FMT_NL, (int8_t)(a8 / b8));

    int16_t a16, b16;
    printf("two int16" FMT_NL);
    scanf("%" SCNd16 " %" SCNd16, &a16, &b16);
    printf("add: %" PRId16 FMT_NL, (int16_t)(a16 + b16));
    printf("mult: %" PRId16 FMT_NL, (int16_t)(a16 * b16));
    printf("div: %" PRId16 FMT_NL FMT_NL, (int16_t)(a16 / b16));

    int32_t a32, b32;
    printf("two int32" FMT_NL);
    scanf("%" SCNd32 " %" SCNd32, &a32, &b32);
    printf("add: %" PRId32 FMT_NL, (int32_t)(a32 + b32));
    printf("mult: %" PRId32 FMT_NL, (int32_t)(a32 * b32));
    printf("div: %" PRId32 FMT_NL FMT_NL, (int32_t)(a32 / b32));

    int64_t a64, b64;
    int32_t temp_a, temp_b;
    printf("two int64 (32-bit to 64 cast)" FMT_NL);
    scanf("%" SCNd32 " %" SCNd32, &temp_a, &temp_b);
    a64 = temp_a;
    b64 = temp_b;
    printf("add: %" PRId32 FMT_NL, (int32_t)(a64 + b64));
    printf("mult: %" PRId32 FMT_NL, (int32_t)(a64 * b64));
    printf("div: %" PRId32 FMT_NL FMT_NL, (int32_t)(a64 / b64));

    float af, bf;
    printf("two floats" FMT_NL);
    scanf("%f %f", &af, &bf);
    printf("add: %f" FMT_NL, af + bf);
    printf("mult: %f" FMT_NL, af * bf);
    printf("div: %f" FMT_NL FMT_NL, af / bf);

    printf("all done" FMT_NL);
}
