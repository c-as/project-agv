#include "lib/serialio.h"
#include "lib/motoren.h"
#include "lib/tof/tof.h"
#include "lib/adc.h"
#include "lib/ldr.h"
#include "lib/navigatie.h"
#include "lib/pwm.h"
#include "lib/time.h"
#include "lib/ldr.h"
#include "lib/ir.h"

void init()
{
    serialio_init();
    tof_init();
    init_motoren();
    adc_init();
    pwm_init();
    ir_init();
}

void start()
{
    // time_test();
    //  tof_test();
    ldr_volgen();
//    agv_start_navigatie();
    while (1)
    {
    }
}

int main()
{
    init();
    start();
}
