#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#endif

#include <avr/io.h>
#include <stdio.h>
#include <util/setbaud.h>

int uart_putchar(char, FILE *);
void uart_init();

FILE output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void uart_init(void)
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8-bit data */
    UCSR0B = (1 << TXEN0);                  /* Enable TX */
}

int uart_putchar(char c, FILE *stream)
{
    if (c == '\n')
    {
        uart_putchar('\r', stream);
    }
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}

void init_print()
{
    uart_init();
    stdout = &output;
}