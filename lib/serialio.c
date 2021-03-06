#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#endif

#include <avr/io.h>
#include <stdio.h>
#include <util/setbaud.h>
#include "time.h"

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

// begin de communicatie
void serialio_init()
{
    uart_init();
    stdout = &output;
}

// elke 500ms wordt er de tekst "test" via de usb verstuurd
void serialio_test()
{
    serialio_init();

    while (1)
    {
        printf("test\n");
        wacht_millis(500);
    }
}

// geeft je nummers weer als eenen en nullen met elke 4 tekens een spatie
void printb(int number, int size)
{
    for (int i = 0; i < size; i++)
    {
        int n = number >> (size - i - 1);

        if (i % 4 == 0)
        {
            printf(" ");
        }

        if (n & 1)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}