#ifndef _PINIO_H_
#define _PINIO_H_

#include <inttypes.h>
#include <stdbool.h>

#define MEGA_PIN_D4 \
    (Pin) { .pDDR = &DDRG, .pPIN = &PING, .pPORT = &PORTG, .pin = PG5 }
#define MEGA_PIN_D0 \
    (Pin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE0 }
#define MEGA_PIN_D1 \
    (Pin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE1 }
#define MEGA_PIN_D5 \
    (Pin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE3 }
#define MEGA_PIN_D2 \
    (Pin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE4 }
#define MEGA_PIN_D3 \
    (Pin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE5 }
#define MEGA_PIN_D17 \
    (Pin) { .pDDR = &DDRH, .pPIN = &PINH, .pPORT = &PORTH, .pin = PH0 }
#define MEGA_PIN_D16 \
    (Pin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE1 }
#define MEGA_PIN_D6 \
    (Pin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE3 }
#define MEGA_PIN_D7 \
    (Pin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE4 }
#define MEGA_PIN_D8 \
    (Pin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE5 }
#define MEGA_PIN_D9 \
    (Pin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE6 }
#define MEGA_PIN_D53 \
    (Pin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB0 }
#define MEGA_PIN_D52 \
    (Pin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB1 }
#define MEGA_PIN_D51 \
    (Pin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB2 }
#define MEGA_PIN_D50 \
    (Pin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB3 }
#define MEGA_PIN_D10 \
    (Pin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB4 }
#define MEGA_PIN_D11 \
    (Pin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB5 }
#define MEGA_PIN_D12 \
    (Pin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB6 }
#define MEGA_PIN_D13 \
    (Pin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB7 }
#define MEGA_PIN_D49 \
    (Pin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL0 }
#define MEGA_PIN_D48 \
    (Pin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL1 }
#define MEGA_PIN_D47 \
    (Pin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL2 }
#define MEGA_PIN_D46 \
    (Pin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL3 }
#define MEGA_PIN_D45 \
    (Pin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL4 }
#define MEGA_PIN_D44 \
    (Pin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL5 }
#define MEGA_PIN_D43 \
    (Pin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL6 }
#define MEGA_PIN_D42 \
    (Pin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL7 }
#define MEGA_PIN_D21 \
    (Pin) { .pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD0 }
#define MEGA_PIN_D20 \
    (Pin) { .pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD1 }
#define MEGA_PIN_D19 \
    (Pin) { .pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD2 }
#define MEGA_PIN_D18 \
    (Pin) { .pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD3 }
#define MEGA_PIN_D38 \
    (Pin) { .pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD7 }
#define MEGA_PIN_D41 \
    (Pin) { .pDDR = &DDRG, .pPIN = &PING, .pPORT = &PORTG, .pin = PG0 }
#define MEGA_PIN_D40 \
    (Pin) { .pDDR = &DDRG, .pPIN = &PING, .pPORT = &PORTG, .pin = PG1 }
#define MEGA_PIN_D37 \
    (Pin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC0 }
#define MEGA_PIN_D36 \
    (Pin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC1 }
#define MEGA_PIN_D35 \
    (Pin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC2 }
#define MEGA_PIN_D34 \
    (Pin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC3 }
#define MEGA_PIN_D33 \
    (Pin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC4 }
#define MEGA_PIN_D32 \
    (Pin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC5 }
#define MEGA_PIN_D31 \
    (Pin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC6 }
#define MEGA_PIN_D30 \
    (Pin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC7 }
#define MEGA_PIN_D15 \
    (Pin) { .pDDR = &DDRJ, .pPIN = &PINJ, .pPORT = &PORTJ, .pin = PJ0 }
#define MEGA_PIN_D14 \
    (Pin) { .pDDR = &DDRJ, .pPIN = &PINJ, .pPORT = &PORTJ, .pin = PJ1 }
#define MEGA_PIN_D39 \
    (Pin) { .pDDR = &DDRG, .pPIN = &PING, .pPORT = &PORTG, .pin = PG2 }
#define MEGA_PIN_D29 \
    (Pin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA7 }
#define MEGA_PIN_D28 \
    (Pin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA6 }
#define MEGA_PIN_D27 \
    (Pin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA5 }
#define MEGA_PIN_D26 \
    (Pin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA4 }
#define MEGA_PIN_D25 \
    (Pin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA3 }
#define MEGA_PIN_D24 \
    (Pin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA2 }
#define MEGA_PIN_D23 \
    (Pin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA1 }
#define MEGA_PIN_D22 \
    (Pin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA0 }
#define MEGA_PIN_A15 \
    (Pin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK7 }
#define MEGA_PIN_A14 \
    (Pin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK6 }
#define MEGA_PIN_A13 \
    (Pin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK5 }
#define MEGA_PIN_A12 \
    (Pin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK4 }
#define MEGA_PIN_A11 \
    (Pin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK3 }
#define MEGA_PIN_A10 \
    (Pin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK2 }
#define MEGA_PIN_A9 \
    (Pin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK1 }
#define MEGA_PIN_A8 \
    (Pin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK0 }
#define MEGA_PIN_A7 \
    (Pin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF7 }
#define MEGA_PIN_A6 \
    (Pin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF6 }
#define MEGA_PIN_A5 \
    (Pin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF5 }
#define MEGA_PIN_A4 \
    (Pin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF4 }
#define MEGA_PIN_A3 \
    (Pin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF3 }
#define MEGA_PIN_A2 \
    (Pin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF2 }
#define MEGA_PIN_A1 \
    (Pin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF1 }
#define MEGA_PIN_A0 \
    (Pin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF0 }

typedef enum // opties voor de werking van elke pin
{
    PINMODE_INPUT,
    PINMODE_INPUT_PULLUP,
    PINMODE_OUTPUT,
} PinMode;

typedef struct // pakket van data voor het gebruik van een specifieke pin
{
    uint8_t *pDDR;
    uint8_t *pPIN;
    uint8_t *pPORT;
    uint8_t pin;
} Pin;

void pin_set_mode(Pin pin, PinMode mode);
void pin_set_output(Pin pin, bool output);
bool pin_get_input(Pin pin);
void pinio_test();

#endif