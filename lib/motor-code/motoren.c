#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "motorenDefines.h"

void init_motoren()
{
    DDR_LPWM1 |= (1 << PIN_LPWM1);
    DDR_LPWM2 |= (1 << PIN_LPWM2);
    DDR_LPWM3 |= (1 << PIN_LPWM3);
    DDR_LPWM4 |= (1 << PIN_LPWM4);
    DDR_RPWM1 |= (1 << PIN_RPWM1);
    DDR_RPWM2 |= (1 << PIN_RPWM2);
    DDR_RPWM3 |= (1 << PIN_RPWM3);
    DDR_RPWM4 |= (1 << PIN_RPWM4);
}


/*
de motor is de motor die je wilt aansturen
de kant is welke kant de motor op draait
1 = met de klok mee(CW)
-1 = tegen de klok in(CCW)
*/
void motor(int motor, int kant)
{
    if (kant == 1)
    {
        switch (motor)
        {
        case 1:
            PORT_LPWM1 &= ~(1 << PIN_LPWM1);
            PORT_RPWM1 |= (1 << PIN_RPWM1);
            break;
        case 2: 
            PORT_LPWM2 &= ~(1 << PIN_LPWM2);
            PORT_RPWM2 |= (1 << PIN_RPWM2);
            break;
        case 3: 
            PORT_LPWM3 &= ~(1 << PIN_LPWM3);
            PORT_RPWM3 |= (1 << PIN_RPWM3);
            break;        
        case 4: 
            PORT_LPWM4 &= ~(1 << PIN_LPWM4);
            PORT_RPWM4 |= (1 << PIN_RPWM4);
            break;
        }
    }
    else if (kant == -1)
    {
        switch (motor)
        {
        case 1:
            PORT_LPWM1 |= (1 << PIN_LPWM1);
            PORT_RPWM1 &= ~(1 << PIN_RPWM1);
            break;
        case 2: 
            PORT_LPWM2 |= (1 << PIN_LPWM2);
            PORT_RPWM2 &= ~(1 << PIN_RPWM2);
            break;
        case 3: 
            PORT_LPWM3 |= (1 << PIN_LPWM3);
            PORT_RPWM3 &= ~(1 << PIN_RPWM3);
            break;        
        case 4: 
            PORT_LPWM4 |= (1 << PIN_LPWM4);
            PORT_RPWM4 &= ~(1 << PIN_RPWM4);
            break;
        }
    }
}

// 1 is vooruit(postitief langs de x-as)
//-1 is achteruit(negatief langs de x-as)
void RijdenX_as(int kant)
{
    if (kant == 1)
    {
        motor(1, -1);
        motor(2, 1);
        motor(3, -1);
        motor(4, 1);
    }
    if (kant == -1)
    {
        motor(1, 1);
        motor(2, -1);
        motor(3, 1);
        motor(4, -1);
    }
}

// 1 is vooruit(postitief langs de y-as)
//-1 is achteruit(negatief langs de y-as)
void RijdenY_as(int kant)
{
    if (kant == 1)
    {
        motor(1, -1);
        motor(2, -1);
        motor(3, 1);
        motor(4, 1);
    }
    if (kant == -1)
    {
        motor(1, 1);
        motor(2, 1);
        motor(3, -1);
        motor(4, -1);
    }
}

// 1 is met de klok mee(CW)
//-1 is tegen de klok in(CCW)
void Draaien(int kant)
{
    if (kant == 1)
    {
        motor(1, -1);
        motor(2, -1);
        motor(3, -1);
        motor(4, -1);
    }
    if (kant == -1)
    {
        motor(1, 1);
        motor(2, 1);
        motor(3, 1);
        motor(4, 1);
    }
}