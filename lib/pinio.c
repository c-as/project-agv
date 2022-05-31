#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "pinio.h"

void pin_set_mode(DigitalPin pin, DigitalPinMode mode)
{
    switch (mode)
    {
    case PINMODE_DIGITAL_INPUT:
        *pin.pDDR &= ~(1 << pin.pin);
        *pin.pPORT &= ~(1 << pin.pin);
        break;
    case PINMODE_DIGITAL_INPUT_PULLUP:
        *pin.pDDR &= ~(1 << pin.pin);
        *pin.pPORT |= (1 << pin.pin); // om de interne pullup weerstand te gebruiken moet de port hoog gezet worden
        break;
    case PINMODE_DIGITAL_OUTPUT:
        *pin.pDDR |= (1 << pin.pin);
        *pin.pPORT &= ~(1 << pin.pin);
        break;
    }
}

// zet de pin hoog(1) of laag(0)
void pin_set_output(DigitalPin pin, bool output)
{
    if (output)
        *pin.pPORT |= (1 << pin.pin);
    else
        *pin.pPORT &= ~(1 << pin.pin);
}

// kijk of pin hoog(1) of laag(0) is
bool pin_get_input(DigitalPin pin)
{
    if (*pin.pPORT & (1 << pin.pin))          // kijk of de interne pullup weerstand wordt gebruikt
        return !(*pin.pPIN & (1 << pin.pin)); // als dat zo is dan moet de waarde omgedraaid worden
    else
        return *pin.pPIN & (1 << pin.pin);
}

// knipper led op poort A12
void pinio_test()
{
    pin_set_mode(MEGA_PIN_A12_DIGITAL, PINMODE_DIGITAL_OUTPUT);

    while (1)
    {
        pin_set_output(MEGA_PIN_A12_DIGITAL, 0);
        _delay_ms(500);
        pin_set_output(MEGA_PIN_A12_DIGITAL, 1);
        _delay_ms(500);
    }
}