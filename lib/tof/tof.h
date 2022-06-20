#ifndef _TOF_H_
#define _TOF_H_

#include "../pinio.h"

#define TOF_1_PIN_X MEGA_PIN_D44_DIGITAL
#define TOF_2_PIN_X MEGA_PIN_D42_DIGITAL
#define TOF_3_PIN_X MEGA_PIN_D46_DIGITAL
#define TOF_4_PIN_X MEGA_PIN_D40_DIGITAL

#define TOF_VOOR TOF_1_PIN_X
#define TOF_ACHTER TOF_2_PIN_X
#define TOF_LINKS TOF_3_PIN_X
#define TOF_RECHTS TOF_4_PIN_X

#define TOF_X_PLUS TOF_VOOR
#define TOF_X_MIN TOF_ACHTER
#define TOF_Y_PLUS TOF_LINKS
#define TOF_Y_MIN TOF_RECHTS

void tof_init();
uint16_t tof_measure(DigitalPin tof_vin_pin);
void tof_test();

#endif
