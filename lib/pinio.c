#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "pinio.h"

Pin get_pin(MegaPins mega_pin)
{
    switch (mega_pin)
    {
    case MEGA_PIN_D4:
        return (Pin){.pDDR = &DDRG, .pPIN = &PING, .pPORT = &PORTG, .pin = PG5};
    case MEGA_PIN_D0:
        return (Pin){.pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE0};
    case MEGA_PIN_D1:
        return (Pin){.pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE1};
    case MEGA_PIN_D5:
        return (Pin){.pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE3};
    case MEGA_PIN_D2:
        return (Pin){.pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE4};
    case MEGA_PIN_D3:
        return (Pin){.pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE5};
    case MEGA_PIN_D17:
        return (Pin){.pDDR = &DDRH, .pPIN = &PINH, .pPORT = &PORTH, .pin = PH0};
    case MEGA_PIN_D16:
        return (Pin){.pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE1};
    case MEGA_PIN_D6:
        return (Pin){.pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE3};
    case MEGA_PIN_D7:
        return (Pin){.pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE4};
    case MEGA_PIN_D8:
        return (Pin){.pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE5};
    case MEGA_PIN_D9:
        return (Pin){.pDDR = &DDRE, .pPIN = &PINE, .pPORT = &PORTE, .pin = PE6};
    case MEGA_PIN_D53:
        return (Pin){.pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB0};
    case MEGA_PIN_D52:
        return (Pin){.pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB1};
    case MEGA_PIN_D51:
        return (Pin){.pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB2};
    case MEGA_PIN_D50:
        return (Pin){.pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB3};
    case MEGA_PIN_D10:
        return (Pin){.pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB4};
    case MEGA_PIN_D11:
        return (Pin){.pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB5};
    case MEGA_PIN_D12:
        return (Pin){.pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB6};
    case MEGA_PIN_D13:
        return (Pin){.pDDR = &DDRB, .pPIN = &PINB, .pPORT = &PORTB, .pin = PB7};
    case MEGA_PIN_D49:
        return (Pin){.pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL0};
    case MEGA_PIN_D48:
        return (Pin){.pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL1};
    case MEGA_PIN_D47:
        return (Pin){.pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL2};
    case MEGA_PIN_D46:
        return (Pin){.pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL3};
    case MEGA_PIN_D45:
        return (Pin){.pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL4};
    case MEGA_PIN_D44:
        return (Pin){.pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL5};
    case MEGA_PIN_D43:
        return (Pin){.pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL6};
    case MEGA_PIN_D42:
        return (Pin){.pDDR = &DDRG, .pPIN = &PINL, .pPORT = &PORTL, .pin = PL7};
    case MEGA_PIN_D21:
        return (Pin){.pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD0};
    case MEGA_PIN_D20:
        return (Pin){.pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD1};
    case MEGA_PIN_D19:
        return (Pin){.pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD2};
    case MEGA_PIN_D18:
        return (Pin){.pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD3};
    case MEGA_PIN_D38:
        return (Pin){.pDDR = &DDRD, .pPIN = &PIND, .pPORT = &PORTD, .pin = PD7};
    case MEGA_PIN_D41:
        return (Pin){.pDDR = &DDRG, .pPIN = &PING, .pPORT = &PORTG, .pin = PG0};
    case MEGA_PIN_D40:
        return (Pin){.pDDR = &DDRG, .pPIN = &PING, .pPORT = &PORTG, .pin = PG1};
    case MEGA_PIN_D37:
        return (Pin){.pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC0};
    case MEGA_PIN_D36:
        return (Pin){.pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC1};
    case MEGA_PIN_D35:
        return (Pin){.pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC2};
    case MEGA_PIN_D34:
        return (Pin){.pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC3};
    case MEGA_PIN_D33:
        return (Pin){.pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC4};
    case MEGA_PIN_D32:
        return (Pin){.pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC5};
    case MEGA_PIN_D31:
        return (Pin){.pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC6};
    case MEGA_PIN_D30:
        return (Pin){.pDDR = &DDRC, .pPIN = &PINC, .pPORT = &PORTC, .pin = PC7};
    case MEGA_PIN_D15:
        return (Pin){.pDDR = &DDRJ, .pPIN = &PINJ, .pPORT = &PORTJ, .pin = PJ0};
    case MEGA_PIN_D14:
        return (Pin){.pDDR = &DDRJ, .pPIN = &PINJ, .pPORT = &PORTJ, .pin = PJ1};
    case MEGA_PIN_D39:
        return (Pin){.pDDR = &DDRG, .pPIN = &PING, .pPORT = &PORTG, .pin = PG2};
    case MEGA_PIN_D29:
        return (Pin){.pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA7};
    case MEGA_PIN_D28:
        return (Pin){.pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA6};
    case MEGA_PIN_D27:
        return (Pin){.pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA5};
    case MEGA_PIN_D26:
        return (Pin){.pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA4};
    case MEGA_PIN_D25:
        return (Pin){.pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA3};
    case MEGA_PIN_D24:
        return (Pin){.pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA2};
    case MEGA_PIN_D23:
        return (Pin){.pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA1};
    case MEGA_PIN_D22:
        return (Pin){.pDDR = &DDRA, .pPIN = &PINA, .pPORT = &PORTA, .pin = PA0};
    case MEGA_PIN_A15:
        return (Pin){.pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK7};
    case MEGA_PIN_A14:
        return (Pin){.pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK6};
    case MEGA_PIN_A13:
        return (Pin){.pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK5};
    case MEGA_PIN_A12:
        return (Pin){.pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK4};
    case MEGA_PIN_A11:
        return (Pin){.pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK3};
    case MEGA_PIN_A10:
        return (Pin){.pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK2};
    case MEGA_PIN_A9:
        return (Pin){.pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK1};
    case MEGA_PIN_A8:
        return (Pin){.pDDR = &DDRK, .pPIN = &PINK, .pPORT = &PORTK, .pin = PK0};
    case MEGA_PIN_A7:
        return (Pin){.pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF7};
    case MEGA_PIN_A6:
        return (Pin){.pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF6};
    case MEGA_PIN_A5:
        return (Pin){.pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF5};
    case MEGA_PIN_A4:
        return (Pin){.pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF4};
    case MEGA_PIN_A3:
        return (Pin){.pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF3};
    case MEGA_PIN_A2:
        return (Pin){.pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF2};
    case MEGA_PIN_A1:
        return (Pin){.pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF1};
    case MEGA_PIN_A0:
        return (Pin){.pDDR = &DDRF, .pPIN = &PINF, .pPORT = &PORTF, .pin = PF0};
    }
}

void pin_set_mode(Pin pin, PinMode mode)
{
    switch (mode)
    {
    case PINMODE_INPUT:
        *pin.pDDR &= ~(1 << pin.pin);
        break;
    case PINMODE_OUTPUT:
        *pin.pDDR |= (1 << pin.pin);
        break;
    }
}

void pin_set_output(Pin pin, bool output)
{
    if (output)
        *pin.pPORT |= (1 << pin.pin);
    else
        *pin.pPORT &= ~(1 << pin.pin);
}

bool pin_get_input(Pin pin)
{
    return *pin.pPIN & (1 << pin.pin);
}

void pinio_test()
{
    // make a led blink on pin A12
    Pin pin = get_pin(MEGA_PIN_A12);
    pin_set_mode(pin, PINMODE_OUTPUT);

    while (1)
    {
        pin_set_output(pin, 0);
        _delay_ms(500);
        pin_set_output(pin, 1);
        _delay_ms(500);
    }
}