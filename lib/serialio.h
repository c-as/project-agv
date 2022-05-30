#ifndef _PRINT_H_
#define _PRINT_H_

#include <stdio.h>

FILE output;

int uart_putchar(char c, FILE *stream);
void uart_init(void);
void serialio_init();
void serialio_test();
void printb(int number, int size);

#endif
