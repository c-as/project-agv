#include <inttypes.h>
#include "tof/vl53l0x-non-arduino/util/millis.h"
#include "pinio.h"
#include <avr/io.h>

void wacht_millis(uint32_t wait)
{
    uint32_t start = millis();

    while (millis() - start < wait)
    {
        ;
    }
}

void time_test()
{
    pin_set_mode(MEGA_PIN_D23_DIGITAL, PINMODE_DIGITAL_OUTPUT);

    while (1)
    {
        pin_set_output(MEGA_PIN_D23_DIGITAL, 1);
        wacht_millis(1000);
        pin_set_output(MEGA_PIN_D23_DIGITAL, 0);
        wacht_millis(1000);
    }
}