#include <avr/io.h>
#define IRsensor3 PC6
#define IRsensor4 PC7

void IRsensoren ()
{
    DDRC &= ~(1<<IRsensor3);
    DDRC &= ~(1<<IRsensor4);
}

void IRsensorenif ()
{
    int IRsensor3_x = !(PINC &(1 << IRsensor3));
    int IRsensor4_x = !(PINC &(1 << IRsensor4));

    if (IRsensor3_x)
    {

    }

    else if (IRsensor4_x)
    {

    }

}
