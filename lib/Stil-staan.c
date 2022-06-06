#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "motoren.h"

void stil_staan()
{
    motor_zet_duty(0);
}
