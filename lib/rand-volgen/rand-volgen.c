/*
 */

#include <avr/io.h>
#include "defines.h"

void motor1(int beweeg) // pins moeten nog goed worden gedefined
{
    if (beweeg == 1)
    {
        PORT_LPWM |= (1 << PIN_LPWM);
    }
    else if (beweeg == 0)
    {
        PORT_LPWM &= ~(1 << PIN_LPWM);
        PORT_RPWM &= ~(1 << PIN_RPWM);
    }
    else if (beweeg == -1)
    {
        PORT_RPWM |= (1 << PIN_RPWM);
    }
}

void motor2(int beweeg) // pins moeten nog goed worden gedefined
{
    if (beweeg == 1)
    {
        PORT_LPWM |= (1 << PIN_LPWM);
    }
    else if (beweeg == 0)
    {
        PORT_LPWM &= ~(1 << PIN_LPWM);
        PORT_RPWM &= ~(1 << PIN_RPWM);
    }
    else if (beweeg == -1)
    {
        PORT_RPWM |= (1 << PIN_RPWM);
    }
}

void motor3(int beweeg) // pins moeten nog goed worden gedefined
{
    if (beweeg == 1)
    {
        PORT_LPWM |= (1 << PIN_LPWM);
    }
    else if (beweeg == 0)
    {
        PORT_LPWM &= ~(1 << PIN_LPWM);
        PORT_RPWM &= ~(1 << PIN_RPWM);
    }
    else if (beweeg == -1)
    {
        PORT_RPWM |= (1 << PIN_RPWM);
    }
}

void motor4(int beweeg) // pins moeten nog goed worden gedefined
{
    if (beweeg == 1)
    {
        PORT_LPWM |= (1 << PIN_LPWM);
    }
    else if (beweeg == 0)
    {
        PORT_LPWM &= ~(1 << PIN_LPWM);
        PORT_RPWM &= ~(1 << PIN_RPWM);
    }
    else if (beweeg == -1)
    {
        PORT_RPWM |= (1 << PIN_RPWM);
    }
}

void bijsturenRandAf()
{
    // Motor 1 vooruit
    motor1(1);
    // Motor 2 achteruit
    motor2(-1);
    // Motor 3 vooruit
    motor3(1);
    // Motor 4 achteruit
    motor4(-1);
}

void bijsturenNaarRandToe()
{
    // Motor 1 achteruit
    motor1(-1);
    // Motor 2 vooruit
    motor2(1);
    // Motor 3 achteruit
    motor3(-1);
    // Motor 4 vooruit
    motor4(1);
}

void RandVolgen()
{
    // ToF 3 < 20
    if (1)
    {
        bijsturenRandAf(); // Moet er nog onder: ToF 3 == 20 ?
    }

    // ToF 3 > 20
    else if (1)
    {
        bijsturenNaarRandToe(); // Moet er nog onder: ToF 3 == 20 ?
    }
}

int main(void)
{
    while (1)
    {
        RandVolgen();
    }

    return 0;
}
