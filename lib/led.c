#include "pinio.h"

void led_init()
{
    pin_set_mode(MEGA_PIN_D39_DIGITAL, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(MEGA_PIN_D43_DIGITAL, PINMODE_DIGITAL_OUTPUT);
}

void led_check(int stand)
{
    if (stand)
    {
        pin_set_output(MEGA_PIN_D39_DIGITAL, 1);
        pin_set_output(MEGA_PIN_D43_DIGITAL, 1);
    }
    else if (stand == 0)
    {

        pin_set_output(MEGA_PIN_D39_DIGITAL, 0);
        pin_set_output(MEGA_PIN_D43_DIGITAL, 0);
    }
}
