#ifndef _TOF_H_
#define _TOF_H_

#include "../pinio.h"

void tof_init();
uint16_t tof_measure(DigitalPin tof_vin_pin);
void tof_test();

#endif