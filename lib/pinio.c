#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include "time.h"
#include "pinio.h"

// kijkt of de pins hetzelfde zijn
bool vergelijk_digital_pins(DigitalPin pin_1, DigitalPin pin_2)
{
    return (pin_1.pDDR == pin_2.pDDR && pin_1.pPIN == pin_2.pPIN && pin_1.pPORT == pin_2.pPORT && pin_1.pin == pin_2.pin);
}

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
        wacht_millis(500);
        pin_set_output(MEGA_PIN_A12_DIGITAL, 1);
        wacht_millis(500);
    }
}