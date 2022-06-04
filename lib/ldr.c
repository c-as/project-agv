/*
 */
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "ldr.h"
#include "adc.h"
#include "motoren.h"

#define MIN_VERSCHIL 30
#define MIN_LICHT 80

#define PIN_LDR0 MEGA_PIN_A0_ANALOG
#define PIN_LDR1 MEGA_PIN_A1_ANALOG

void ldr_vergelijken()
{
    // verschil bestaat
    if (abs(adc_convert(PIN_LDR0) - adc_convert(PIN_LDR1)) > MIN_VERSCHIL)
    {
        // LDR 1 < 2
        if (adc_convert(PIN_LDR0) < adc_convert(PIN_LDR1))
        {
            // Rechtsom draaien
            motor(1, 1);
            motor(2, -1);
            motor(3, 1);
            motor(4, -1);

            printf("ldr: motors rechts\n");

            while (1)
            {
                // LDR 1 == 2
                if (abs(adc_convert(PIN_LDR0) - adc_convert(PIN_LDR1)) < MIN_VERSCHIL)
                {
                    // motoren stoppen
                    motor(1, 0);
                    motor(2, 0);
                    motor(3, 0);
                    motor(4, 0);
                    printf("ldr: motors uit\n");
                    break;
                }
            }
        }
        // LDR 1 > 2
        else
        {
            // Linksom draaien
            motor(1, -1);
            motor(2, 1);
            motor(3, -1);
            motor(4, 1);
            printf("ldr: motors links\n");

            while (1)
            {
                // LDR 1 == 2
                if (abs(adc_convert(PIN_LDR0) - adc_convert(PIN_LDR1)) < MIN_VERSCHIL) /// waarden geven wss niet precies dezelfde waarde, dus ff nog oplossing
                {
                    // motoren stoppen
                    motor(1, 0);
                    motor(2, 0);
                    motor(3, 0);
                    motor(4, 0);
                    printf("ldr: motors uit\n");
                    break;
                }
            }
        }
    }
}

void ldr_volgen()
{
    while (1)
    {
        // LDR > 100
        if (adc_convert(PIN_LDR0) < MIN_LICHT || adc_convert(PIN_LDR1) < MIN_LICHT)
        {
            // ToF 1 en 2 > 20
            if (1)
            {
                printf("ldr: vergelijken\n");
                while (1)
                {
                    ldr_vergelijken();
                }
            }
            // ToF 1 en 2 < 20
            else
            {
                // Motoren uit
                motor(1, 0);
                motor(2, 0);
                motor(3, 0);
                motor(4, 0);
                printf("ldr: motors uit\n");
            }
        }
        printf("get_light0: %i\n", adc_convert(PIN_LDR0));
        printf("get_light1: %i\n", adc_convert(PIN_LDR1));
        _delay_ms(100);
    }
}
