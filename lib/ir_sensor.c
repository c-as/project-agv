// #include <avr/io.h>
// #include "motoren.h"
// #define IRsensor3 PC6
// #define IRsensor4 PC7

// void initTimer0 (void)
// {
//     TCCR0A = 0;
//     TCCR0B = TCCR0B | (1<<CS01) | (1<<CS00);
//     TIMSK0 = TIMSK0 | (1<< TOIE0);
// }

// void IRsensoren ()
// {
//     DDRC &= ~(1<<IRsensor3);
//     DDRC &= ~(1<<IRsensor4);
// }

// ISR (TIMER0_OVF_vect)
// {
//     int IRsensor3_x = !(PINC &(1 << IRsensor3));
//     int IRsensor4_x = !(PINC &(1 << IRsensor4));

//     if (IRsensor3_x)
//     {
//         rijden_stop();
//     }

//     else if (IRsensor4_x)
//     {
//         rijden_stop();
//     }

// }
