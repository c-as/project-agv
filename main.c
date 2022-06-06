#include "lib/serialio.h"
#include "lib/motoren.h"
#include "lib/i2c.h"
#include "lib/tof.h"
#include "lib/adc.h"
#include "lib/ldr.h"
#include "lib/pinio.h"

void init()
{
    serialio_init();
    adc_init();
    init_motoren();
    pwm_init();
    i2c_init();
    tof_init();
}

void start()
{
    // pinio_test();
    // serialio_test();
    tof_test();
    // ldr_volgen();
    // motor(1, MOTORRICHTING_CCW);
    // motor(2, MOTORRICHTING_CCW);
    // motor(3, MOTORRICHTING_CCW);
    // motor(4, MOTORRICHTING_CCW);
    // adc_test();
    // i2c_test();
    // pinio_test_pwm();
    // vec_test();
    // pwm_test();
}

int main()
{
    init();
    start();
}
