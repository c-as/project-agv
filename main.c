#include "lib/serialio.h"
#include "lib/motor-code/motoren.h"
#include "lib/tof/tof.h"
#include "lib/adc.h"
#include "lib/ldr/ldr.h"

void init()
{
    serialio_init();
    adc_init();
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
    motor(1, MOTORRICHTING_CW);
    motor(2, MOTORRICHTING_CW);
    motor(3, MOTORRICHTING_CW);
    motor(4, MOTORRICHTING_CW);
}

int main()
{
    init();
    start();
}
