#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>
#include <inttypes.h>
#include "time.h"
#include "adc.h"

#define DEFAULT_REF (0 << REFS1) | (1 << REFS0) // referentiespanning is avcc (5v)

void adc_init()
{
    ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // klokdeler
    ADCSRA |= (1 << ADEN);                               // zet adc aan
}

bool vergelijk_analoge_pins(AnalogPin pin_1, AnalogPin pin_2)
{
    return (pin_1.mux2 == pin_2.mux2 && pin_1.mux5 == pin_2.mux5);
}

// geeft een getal tussen de 0 (= 0v) en de 1024 (= 5v)
uint16_t adc_convert(AnalogPin pin)
{
    ADMUX = DEFAULT_REF | pin.mux2;            // zet referentiespanning en pin
    ADCSRB = (1 << ACME) | (pin.mux5 << MUX5); // enable multiplexer en zet mux5 voor pins hoger dan 7
    ADCSRA |= (1 << ADSC);                     // start conversie
    while (ADCSRA & (1 << ADSC))               // wacht totdat conversie klaar is
    {
        ;
    }
    return ADC;
}

// lees spanning op pin A15
void adc_test()
{
    while (1)
    {
        printf("adc measurement: %i\n", adc_convert(MEGA_PIN_A15_ANALOG));
        wacht_millis(500);
    }
}