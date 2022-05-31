#include "lib/motor-code/motoren.h"
#include "lib/pinio.h"
#include "lib/serialio.h"
#include "lib/tof/tof.h"

void init()
{
    init_motoren();
    serialio_init();
    tof_init();
}

void start()
{
    // pinio_test();
    // serialio_test();
    tof_test();
}

int main()
{
    init();
    start();
}
