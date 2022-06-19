#include "lib/serialio.h"
#include "lib/motoren.h"
#include "lib/tof/tof.h"
#include "lib/adc.h"
#include "lib/ldr.h"
#include "lib/navigatie.h"
#include "lib/pwm.h"
#include "lib/time.h"

void init()
{
    serialio_init();
    tof_init();
    init_motoren();
    adc_init();
    pwm_init();
}

void start()
{
    // time_test();
    //  tof_test();
    agv_start_navigatie();
}

int main()
{
    init();
    start();
}
