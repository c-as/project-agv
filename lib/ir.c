#include <stdbool.h>
#include "motoren.h"
#include "pinio.h"
#include "time.h"
#include "ir.h"
#include "led.h"

#define IR_1 MEGA_PIN_D31_DIGITAL
#define IR_2 MEGA_PIN_D30_DIGITAL

#define IR_LINKS IR_1
#define IR_RECHTS IR_2

#define WACHTTIJD_BOOM_MS 2000

volatile bool last_ir_1 = false;
volatile bool last_ir_2 = false;

void ir_init()
{
    pin_set_mode(IR_1, PINMODE_DIGITAL_INPUT_PULLUP);
    pin_set_mode(IR_2, PINMODE_DIGITAL_INPUT_PULLUP);

    ir_1_enabled = true;
    ir_2_enabled = true;
}

void ir_check()
{
    volatile int vorige_rijrichting = current_rijrichting;
    volatile int vorige_duty = current_duty;

    if (pin_get_input(IR_1) && (!last_ir_1) && ir_1_enabled)
    {
        last_ir_1 = true;
        rijden_stop();
        led_check(1);
        wacht_millis(WACHTTIJD_BOOM_MS);
        rijden(vorige_rijrichting, vorige_duty);
    }
    else if ((!pin_get_input(IR_1)) && last_ir_1)
    {
        last_ir_1 = false;
        led_check(0);
    }

    if (pin_get_input(IR_2) && (!last_ir_2) && ir_2_enabled)
    {
        last_ir_2 = true;
        rijden_stop();
        led_check(1);
        wacht_millis(WACHTTIJD_BOOM_MS);
        rijden(vorige_rijrichting, vorige_duty);
    }
    else if ((!pin_get_input(IR_2)) && last_ir_2)
    {
        last_ir_2 = false;
        led_check(0);
    }
}
