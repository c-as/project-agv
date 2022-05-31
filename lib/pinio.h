#ifndef _PINIO_H_
#define _PINIO_H_

#include <inttypes.h>
#include <stdbool.h>

#define MEGA_PIN_D4_DIGITAL \
    (DigitalPin) { .pDDR = &DDRG, .pPIN = &PING, .pPORT = &PORTG, .pin = PG5 }
#define MEGA_PIN_D0_DIGITAL \
    (DigitalPin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE0 }
#define MEGA_PIN_D1_DIGITAL \
    (DigitalPin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE1 }
#define MEGA_PIN_D5_DIGITAL \
    (DigitalPin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE3 }
#define MEGA_PIN_D2_DIGITAL \
    (DigitalPin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE4 }
#define MEGA_PIN_D3_DIGITAL \
    (DigitalPin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE5 }
#define MEGA_PIN_D17_DIGITAL \
    (DigitalPin) { .pDDR = &DDRH, .pPIN = &PINH, .pPORT = &PORTH, .pin = PH0 }
#define MEGA_PIN_D16_DIGITAL \
    (DigitalPin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE1 }
#define MEGA_PIN_D6_DIGITAL \
    (DigitalPin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE3 }
#define MEGA_PIN_D7_DIGITAL \
    (DigitalPin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE4 }
#define MEGA_PIN_D8_DIGITAL \
    (DigitalPin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE5 }
#define MEGA_PIN_D9_DIGITAL \
    (DigitalPin) { .pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE6 }
#define MEGA_PIN_D53_DIGITAL \
    (DigitalPin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB0 }
#define MEGA_PIN_D52_DIGITAL \
    (DigitalPin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB1 }
#define MEGA_PIN_D51_DIGITAL \
    (DigitalPin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB2 }
#define MEGA_PIN_D50_DIGITAL \
    (DigitalPin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB3 }
#define MEGA_PIN_D10_DIGITAL \
    (DigitalPin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB4 }
#define MEGA_PIN_D11_DIGITAL \
    (DigitalPin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB5 }
#define MEGA_PIN_D12_DIGITAL \
    (DigitalPin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB6 }
#define MEGA_PIN_D13_DIGITAL \
    (DigitalPin) { .pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB7 }
#define MEGA_PIN_D49_DIGITAL \
    (DigitalPin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL0 }
#define MEGA_PIN_D48_DIGITAL \
    (DigitalPin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL1 }
#define MEGA_PIN_D47_DIGITAL \
    (DigitalPin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL2 }
#define MEGA_PIN_D46_DIGITAL \
    (DigitalPin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL3 }
#define MEGA_PIN_D45_DIGITAL \
    (DigitalPin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL4 }
#define MEGA_PIN_D44_DIGITAL \
    (DigitalPin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL5 }
#define MEGA_PIN_D43_DIGITAL \
    (DigitalPin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL6 }
#define MEGA_PIN_D42_DIGITAL \
    (DigitalPin) { .pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL7 }
#define MEGA_PIN_D21_DIGITAL \
    (DigitalPin) { .pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD0 }
#define MEGA_PIN_D20_DIGITAL \
    (DigitalPin) { .pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD1 }
#define MEGA_PIN_D19_DIGITAL \
    (DigitalPin) { .pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD2 }
#define MEGA_PIN_D18_DIGITAL \
    (DigitalPin) { .pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD3 }
#define MEGA_PIN_D38_DIGITAL \
    (DigitalPin) { .pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD7 }
#define MEGA_PIN_D41_DIGITAL \
    (DigitalPin) { .pDDR = &DDRG, .pPIN = &PING, .pPORT = &PORTG, .pin = PG0 }
#define MEGA_PIN_D40_DIGITAL \
    (DigitalPin) { .pDDR = &DDRG, .pPIN = &PING, .pPORT = &PORTG, .pin = PG1 }
#define MEGA_PIN_D37_DIGITAL \
    (DigitalPin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC0 }
#define MEGA_PIN_D36_DIGITAL \
    (DigitalPin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC1 }
#define MEGA_PIN_D35_DIGITAL \
    (DigitalPin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC2 }
#define MEGA_PIN_D34_DIGITAL \
    (DigitalPin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC3 }
#define MEGA_PIN_D33_DIGITAL \
    (DigitalPin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC4 }
#define MEGA_PIN_D32_DIGITAL \
    (DigitalPin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC5 }
#define MEGA_PIN_D31_DIGITAL \
    (DigitalPin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC6 }
#define MEGA_PIN_D30_DIGITAL \
    (DigitalPin) { .pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC7 }
#define MEGA_PIN_D15_DIGITAL \
    (DigitalPin) { .pDDR = &DDRJ, .pPIN = &PINJ, .pPORT = &PORTJ, .pin = PJ0 }
#define MEGA_PIN_D14_DIGITAL \
    (DigitalPin) { .pDDR = &DDRJ, .pPIN = &PINJ, .pPORT = &PORTJ, .pin = PJ1 }
#define MEGA_PIN_D39_DIGITAL \
    (DigitalPin) { .pDDR = &DDRG, .pPIN = &PING, .pPORT = &PORTG, .pin = PG2 }
#define MEGA_PIN_D29_DIGITAL \
    (DigitalPin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA7 }
#define MEGA_PIN_D28_DIGITAL \
    (DigitalPin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA6 }
#define MEGA_PIN_D27_DIGITAL \
    (DigitalPin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA5 }
#define MEGA_PIN_D26_DIGITAL \
    (DigitalPin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA4 }
#define MEGA_PIN_D25_DIGITAL \
    (DigitalPin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA3 }
#define MEGA_PIN_D24_DIGITAL \
    (DigitalPin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA2 }
#define MEGA_PIN_D23_DIGITAL \
    (DigitalPin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA1 }
#define MEGA_PIN_D22_DIGITAL \
    (DigitalPin) { .pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA0 }
#define MEGA_PIN_A15_DIGITAL \
    (DigitalPin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK7 }
#define MEGA_PIN_A14_DIGITAL \
    (DigitalPin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK6 }
#define MEGA_PIN_A13_DIGITAL \
    (DigitalPin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK5 }
#define MEGA_PIN_A12_DIGITAL \
    (DigitalPin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK4 }
#define MEGA_PIN_A11_DIGITAL \
    (DigitalPin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK3 }
#define MEGA_PIN_A10_DIGITAL \
    (DigitalPin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK2 }
#define MEGA_PIN_A9_DIGITAL \
    (DigitalPin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK1 }
#define MEGA_PIN_A8_DIGITAL \
    (DigitalPin) { .pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK0 }
#define MEGA_PIN_A7_DIGITAL \
    (DigitalPin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF7 }
#define MEGA_PIN_A6_DIGITAL \
    (DigitalPin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF6 }
#define MEGA_PIN_A5_DIGITAL \
    (DigitalPin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF5 }
#define MEGA_PIN_A4_DIGITAL \
    (DigitalPin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF4 }
#define MEGA_PIN_A3_DIGITAL \
    (DigitalPin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF3 }
#define MEGA_PIN_A2_DIGITAL \
    (DigitalPin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF2 }
#define MEGA_PIN_A1_DIGITAL \
    (DigitalPin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF1 }
#define MEGA_PIN_A0_DIGITAL \
    (DigitalPin) { .pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF0 }

// opties voor de werking van elke pin
typedef enum
{
    PINMODE_DIGITAL_INPUT,
    PINMODE_DIGITAL_INPUT_PULLUP,
    PINMODE_DIGITAL_OUTPUT,
} DigitalPinMode;

// pakket van data voor het gebruik van een specifieke pin
typedef struct
{
    volatile uint8_t *pDDR;
    volatile uint8_t *pPIN;
    volatile uint8_t *pPORT;
    volatile uint8_t pin;
} DigitalPin;

void pin_set_mode(DigitalPin pin, DigitalPinMode mode);
void pin_set_output(DigitalPin pin, bool output);
bool pin_get_input(DigitalPin pin);
void pinio_test();

#endif