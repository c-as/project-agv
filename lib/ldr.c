#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "ldr.h"
#include "adc.h"
#include "motoren.h"
#include "tof/tof.h"

#define MIN_VERSCHIL 30
#define MIN_LICHT 80
#define MIN_AFSTAND_MM 35
#define VOLG_SNELHEID 100
#define DRAAI_SNELHEID 50

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
            rijden(RIJRICHTING_CW, DRAAI_SNELHEID);
            printf("ldr: motors rechts\n");
        }
        // LDR 1 > 2
        else
        {
            // Linksom draaien
            rijden(RIJRICHTING_CCW, DRAAI_SNELHEID);
            printf("ldr: motors links\n");
        }
    }
    else
    {
        rijden(RIJRICHTING_VOORUIT, VOLG_SNELHEID);
    }
}

void ldr_volgen()
{
    // als tof sensoren genoeg afstand meten volg anders stop
    if (tof_measure(TOF_1_PIN_X) > MIN_AFSTAND_MM && tof_measure(TOF_2_PIN_X) > MIN_AFSTAND_MM)
    {
        printf("ldr: vergelijken\n");
        ldr_vergelijken();
    }
    else
    {
        rijden_stop();
        printf("ldr: motors uit\n");
    }
}

void ldr_check()
{
    // als er genoeg licht is begin volgen
    while (adc_convert(PIN_LDR0) < MIN_LICHT || adc_convert(PIN_LDR1) < MIN_LICHT)
    {
        ldr_volgen();
    }
}
