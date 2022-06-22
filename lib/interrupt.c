#include <avr/io.h>
#include <avr/interrupt.h>

void init_interrupt()
{
    EIMSK |= (1 << INT0); // enable external interrupts
    sei();                // enable interrupts
}

void external_interrupt()
{
}

ISR(INT0_vect)
{
    external_interrupt();
}