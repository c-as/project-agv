#include <avr/interrupt.h>
#include "ir.h"
#include "ldr.h"
#include "bumper.h"

void interrupt_init()
{
    TCCR1A = 0;
    TCCR1B = (1 << CS10);  // prescaler
    TIMSK1 = (1 << TOIE1); // overflow interrupts aan
    sei();                 // enbale interrupts
}

ISR(TIMER1_OVF_vect)
{
    TIMSK1 = 0; // zet interrupts van deze timer uit zodat er niet meerdere tegelijkertijd runnen

    ir_check();
    bumper_check();
    ldr_check();

    TIMSK1 = (1 << TOIE1); // overflow interrupts weer aan
}
