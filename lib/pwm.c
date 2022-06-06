#include <avr/interrupt.h>
#include "pinio.h"
#include "pwm.h"
#include <util/delay.h>

#define AMOUNT_PWM_PINS 8

DigitalPin pwm_pinsa[AMOUNT_PWM_PINS];
DigitalPin pwm_pinsb[AMOUNT_PWM_PINS];

void pwm_init()
{
    TCCR2A = 0;
    TCCR2B = (0 << CS20) | (1 << CS21) | (1 << CS22); // 32 prescaler
    TIMSK2 = (1 << TOIE2);                            // enable compare match interrupt A + overflow
    sei();
}

ISR(TIMER2_OVF_vect)
{
    for (int i = 0; i < AMOUNT_PWM_PINS; i++)
    {
        pin_set_output(pwm_pinsa[i], 1);
        pin_set_output(pwm_pinsb[i], 1);
    }
}

ISR(TIMER2_COMPA_vect)
{
    for (int i = 0; i < AMOUNT_PWM_PINS; i++)
    {
        pin_set_output(pwm_pinsa[i], 0);
    }
}

ISR(TIMER2_COMPB_vect)
{
    for (int i = 0; i < AMOUNT_PWM_PINS; i++)
    {
        pin_set_output(pwm_pinsb[i], 0);
    }
}

// zet de duty cycle van een pwm pins groep
void pwm_group_set_duty(PwmGroup group, uint8_t duty)
{
    if (group == PWMGROUP_A)
    {
        if (duty > 0)
        {
            OCR2A = duty;
            TIMSK2 |= (1 << OCIE2A);
        }
        else
        {
            TIMSK2 &= ~(1 << OCIE2A);
        }
    }
    else if (group == PWMGROUP_B)
    {
        if (duty > 0)
        {
            OCR2B = duty;
            TIMSK2 |= (1 << OCIE2B);
        }
        else
        {
            TIMSK2 &= ~(1 << OCIE2B);
        }
    }
}

// zet een pin in een pwm pin groep op plaats i
void pwm_pin_set_group(DigitalPin pin, uint8_t i, PwmGroup group)
{
    if (group == PWMGROUP_A)
    {
        pwm_pinsa[i] = pin;
    }
    else if (group == PWMGROUP_B)
    {
        pwm_pinsb[i] = pin;
    }
}

// golf led op poort D39 en D41
void pwm_test()
{
    pin_set_mode(MEGA_PIN_D39_DIGITAL, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(MEGA_PIN_D41_DIGITAL, PINMODE_DIGITAL_OUTPUT);

    int counta = 21;
    int countb = 21;
    while (1)
    {
        pwm_pin_set(MEGA_PIN_D39_DIGITAL, 0, PWMGROUP_A, counta);
        pwm_pin_set(MEGA_PIN_D41_DIGITAL, 0, PWMGROUP_B, countb);
        counta = (counta + 1) % 255;
        countb = (countb + 10) % 255;
        _delay_ms(10);
    }
}