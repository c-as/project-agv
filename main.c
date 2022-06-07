#include "lib/serialio.h"
#include "lib/motoren.h"
#include "lib/tof/tof.h"
#include "lib/adc.h"
#include "lib/ldr.h"

void init()
{
    serialio_init();
    tof_init();
    initTimer0();
}

void start()
{
    tof_test();
}

int main()
{
    init();
    start();
}
