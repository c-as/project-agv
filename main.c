#include "lib/serialio.h"
#include "lib/tof/tof.h"
#include "lib/adc.h"
#include "lib/navigatie.h"
#include "lib/ir.h"
#include "lib/motoren.h"
#include "lib/interrupt.h"
#include "lib/ldr.h"
#include "lib/bumper.h"
#include "lib/pwm.h"
#include "lib/led.h"

void init()
{
    serialio_init();
    tof_init();
    motoren_init();
    adc_init();
    pwm_init();
    ir_init();
    interrupt_init();
    ldr_init();
    bumper_init();
    led_init();
}

void start()
{

    // tof_test();
    agv_start_navigatie();

    while (1)
    {
        ;
    }
}

int main()
{
    init();
    start();
}
