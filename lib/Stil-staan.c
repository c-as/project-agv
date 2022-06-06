#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "motoren.h"

void stil_staan()
{
    motor(1, MOTORRICHTING_STOP);
    motor(2, MOTORRICHTING_STOP);
    motor(3, MOTORRICHTING_STOP);
    motor(4, MOTORRICHTING_STOP);
}
