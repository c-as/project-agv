#include <stdbool.h>
#include "motoren.h"
#include "tof/tof.h"
#include "time.h"
#include "stdlib.h"
#include "adc.h"

// op het moment alleen de voorste 2
#define PIN_LDR1 MEGA_PIN_A8_ANALOG
#define PIN_LDR2 MEGA_PIN_A10_ANALOG

#define LDR_VOOR_LINKS PIN_LDR1
#define LDR_VOOR_RECHTS PIN_LDR2

#define MIN_VERSCHIL 170
#define MIN_LICHT 150
#define MIN_AFSTAND_MM 100
#define VOLG_SNELHEID 90
#define DRAAI_SNELHEID 100

volatile bool was_volgen = false;

volatile int baseline_ldr_1 = 0;
volatile int baseline_ldr_2 = 0;

void ldr_init()
{
    // de ldrs hebben grote verschillen in dezelfde omstandigheden dus we slaan de begin situatie op
    baseline_ldr_1 = adc_convert(PIN_LDR1);
    baseline_ldr_2 = adc_convert(PIN_LDR2);
}

// lees het de hoeveelheid licht (positief+) ten opzichte van de begin situatie.
int ldr_light(AnalogPin ldr_pin)
{
    if (vergelijk_analoge_pins(ldr_pin, PIN_LDR1))
        return baseline_ldr_1 - adc_convert(PIN_LDR1);
    else if (vergelijk_analoge_pins(ldr_pin, PIN_LDR2))
        return baseline_ldr_2 - adc_convert(PIN_LDR2);

    return -1;
}

void ldr_vergelijken()
{
    // verschil bestaat anders vooruit
    if (abs(ldr_light(LDR_VOOR_LINKS) - ldr_light(LDR_VOOR_RECHTS)) > MIN_VERSCHIL)
    {
        // draai richting de met meer licht
        if (ldr_light(LDR_VOOR_LINKS) < ldr_light(LDR_VOOR_RECHTS))
        {
            rijden(RIJRICHTING_CW, DRAAI_SNELHEID);
        }
        else
        {
            rijden(RIJRICHTING_CCW, DRAAI_SNELHEID);
        }
    }
    else
    {
        rijden(RIJRICHTING_VOORUIT, VOLG_SNELHEID);
    }
}

void ldr_volgen()
{
    // if (tof_measure(TOF_VOOR) > MIN_AFSTAND_MM)
    if (1)
    {
        ldr_vergelijken();
    }
    else
    {
        rijden_stop();
    }
}

void ldr_check()
{
    // als er genoeg licht is begin volgen
    while (ldr_light(PIN_LDR1) > MIN_LICHT || ldr_light(PIN_LDR2) > MIN_LICHT)
    {
        was_volgen = true;

        ldr_volgen();
    }
    if (was_volgen)
    {
        was_volgen = false;
        rijden_stop();
        wacht_millis(2000);
    }
}
