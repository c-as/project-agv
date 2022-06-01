#include "lib/motor-code/motoren.h"
#include "lib/pinio.h"
#include "lib/serialio.h"
#include "lib/tof/tof.h"
#include "lib/adc.h"
#include "lib/ldr/ldr.h"

void init()
{
    init_motoren();
    serialio_init();
    adc_init();
    init_ldr();
    init_motoren();
    // tof_init();
}

void start()
{
    // pinio_test();
    // serialio_test();
    // tof_test();
    // adc_test();
    // ldr_volgen();
    RijdenX_as(0);
}

int main()
{
    init();
    start();
}
