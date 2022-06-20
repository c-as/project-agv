#include <avr/io.h>
#include "motoren.h"
#include "pinio.h"
#include "time.h"

#define IR_1 MEGA_PIN_D31_DIGITAL
#define IR_2 MEGA_PIN_D30_DIGITAL
#define WACHTTIJD_MILLIS 1000

void ir_init()
{
    pin_set_mode(IR_1, PINMODE_DIGITAL_INPUT);
    pin_set_mode(IR_2, PINMODE_DIGITAL_INPUT);
}

void check_ir()
{
    if (pin_get_input(IR_1))
    {
        rijden_stop();
        wacht_millis(WACHTTIJD_MILLIS);
    }
    if (pin_get_input(IR_2))
    {
        rijden_stop();
        wacht_millis(WACHTTIJD_MILLIS);
    }
}
