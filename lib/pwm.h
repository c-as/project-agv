#ifndef _PWM_H_
#define _PWM_H_

#include <inttypes.h>
#include "pinio.h"

typedef enum
{
    PWMGROUP_A,
    PWMGROUP_B,
} PwmGroup;

void pwm_init();
void pwm_group_set_duty(PwmGroup group, uint8_t duty);
void pwm_pin_set_group(DigitalPin pin, uint8_t i, PwmGroup group);
void pwm_pin_set(DigitalPin pin, uint8_t i, PwmGroup group, uint8_t duty);
void pwm_test();

#endif