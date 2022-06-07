#ifndef _TOF_H_
#define _TOF_H_

#include "../pinio.h"

#define TOF_1_PIN MEGA_PIN_D44_DIGITAL
#define TOF_2_PIN MEGA_PIN_D45_DIGITAL
#define TOF_3_PIN MEGA_PIN_D46_DIGITAL
#define TOF_4_PIN MEGA_PIN_D47_DIGITAL

void tof_init();
uint16_t tof_measure(DigitalPin tof_vin_pin);
void tof_test();

#endif