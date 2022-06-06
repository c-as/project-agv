#ifndef _PWM_H_
#define _PWM_H_

#include <inttypes.h>
#include "pinio.h"
#include "vec.h"

// pakket van data die een groep van pins met dezelfde duty cycle onthoud
typedef struct
{
    volatile uint8_t duty;
    volatile Vec *pins;
} PwmGroup;

void pwm_init();
int pwm_pin_set(DigitalPin pin, uint8_t duty);
void pwm_test();

#endif