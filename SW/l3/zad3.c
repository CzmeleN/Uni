#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define LED PC1
#define LED_DDR DDRC
#define LED_PORT PORTC

#define DELAY 1000
#define COUNTS 3

#define N 9
#define STEP 114

// 62.5 Hz - niezauważalne mryganie
static const uint16_t delays[N] = {
    0,
    125,
    250,
    500,
    1000,
    2000,
    4000,
    8000,
    16000,
};

void shine(uint8_t id) {
    LED_PORT |= _BV(LED);

    switch (id) {
        case 0:
            _delay_us(delays[0]);
            break;
        case 1:
            _delay_us(delays[1]);
            break;
        case 2:
            _delay_us(delays[2]);
            break;
        case 3:
            _delay_us(delays[3]);
            break;
        case 4:
            _delay_us(delays[4]);
            break;
        case 5:
            _delay_us(delays[5]);
            break;
        case 6:
            _delay_us(delays[6]);
            break;
        case 7:
            _delay_us(delays[7]);
            break;
        case 8:
            _delay_us(delays[8]);
            break;
    }

    LED_PORT &= ~_BV(LED);

    switch (id) {
        case 0:
            _delay_us(delays[N - 1] - delays[0]);
            break;
        case 1:
            _delay_us(delays[N - 1] - delays[1]);
            break;
        case 2:
            _delay_us(delays[N - 1] - delays[2]);
            break;
        case 3:
            _delay_us(delays[N - 1] - delays[3]);
            break;
        case 4:
            _delay_us(delays[N - 1] - delays[4]);
            break;
        case 5:
            _delay_us(delays[N - 1] - delays[5]);
            break;
        case 6:
            _delay_us(delays[N - 1] - delays[6]);
            break;
        case 7:
            _delay_us(delays[N - 1] - delays[7]);
            break;
        case 8:
            _delay_us(delays[N - 1] - delays[8]);
            break;
    }
}

// inicjalizacja UART
void uart_init()
{
    // ustaw baudrate
    UBRR0 = UBRR_VALUE;
    // włącz odbiornik i nadajnik
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
    // ustaw format 8n1
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
    // czekaj aż transmiter gotowy
    while (!(UCSR0A & _BV(UDRE0)));
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

// inicjalizacja ADC
void adc_init()
{
    ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
    DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
    // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
    ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
    ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;

int main()
{
    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    LED_DDR |= _BV(LED);

    // zainicjalizuj ADC
    adc_init();

    // mierz napięcie
    while(1) {
        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
        ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
        uint16_t v = ADC; // weź zmierzoną wartość (0..1023)

        // for (uint16_t i = STEP - 1; i < v; i += STEP) id++;
        
        shine(v / STEP);
    }
}

