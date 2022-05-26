#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lib/serialio.h"
#include "motor code/motorenDefines.h"
#include "init.c"
#include "motor code/motoren.c"

int motorselector = 0;

void test()
{
}
int main()
{
    init_print();
    init();
    test();
}