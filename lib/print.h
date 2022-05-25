#ifndef _PRINT_H_
#define _PRINT_H_

FILE output;

int uart_putchar(char c, FILE *stream);
void uart_init(void);
void init_print();

#endif
