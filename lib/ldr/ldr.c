/*
 */

#include <avr/io.h>
#include <util/delay.h>

// ADC Initialisatie
void init_adc(void)
{
    ADMUX = (0 << REFS1) | (1 << REFS0);
    ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADCSRA |= (1 << ADEN);
}

int map(int x, int in_min, int in_max, int out_min, int out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Voor LDR boven (vanaf bovenkant)
uint16_t get_LightLevel_1()
{
    _delay_ms(10);
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC))
        ;

    _delay_ms(10);
    return (ADC); // Return 10-bit result
}

// Voor LDR beneden (vanaf bovenkant)
uint16_t get_LightLevel_2()
{
    _delay_ms(10);
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC))
        ;

    _delay_ms(10);
    return (ADC); // Return 10-bit result
}

void ldr_vergelijken()
{
    // LDR 1 < 2
    if ((map(get_LightLevel_1(), 0, 1023, 0, 3)) < (map(get_LightLevel_2(), 0, 1023, 0, 3)))
    {
        // Rechtsom draaien

        while (1)
        {
            if ((map(get_LightLevel_1(), 0, 1023, 0, 3)) == (map(get_LightLevel_2(), 0, 1023, 0, 3)))
            {
                // Stop motoren
                // Vooruit rijden

                break;
            }
        }
    }
    // LDR 1 > 2
    else if ((map(get_LightLevel_1(), 0, 1023, 0, 3)) > (map(get_LightLevel_2(), 0, 1023, 0, 3)))
    {
        // Linksom draaien

        while (1)
        {
            if ((map(get_LightLevel_1(), 0, 1023, 0, 3)) == (map(get_LightLevel_2(), 0, 1023, 0, 3)))
            {
                // Stop motoren
                // Vooruit rijden

                break;
            }
        }
    }
}

void ldr_volgen()
{
    while (1)
    {
        // ToF 1 en 2 > 20
        if (1)
        {
            while (1)
            {
                ldr_vergelijken();
            }
        }
        // ToF 1 en 2 < 20
        else
        {
            // Motoren uit
        }
    }
}
