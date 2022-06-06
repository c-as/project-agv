#include <avr/interrupt.h>
#include "pinio.h"
#include "pwm.h"
#include <util/delay.h>

#define AMOUNT_PWM_PINS 8

DigitalPin pwm_pinsa[AMOUNT_PWM_PINS] = {0};
DigitalPin pwm_pinsb[AMOUNT_PWM_PINS] = {0};

void pwm_init()
{
    TCCR2A = 0;
    TCCR2B = (0 << CS20) | (1 << CS21) | (1 << CS22); // 32 prescaler
    TIMSK2 = (1 << TOIE2);                            // enable compare match interrupt A + overflow
    sei();
}

ISR(TIMER2_OVF_vect)
{
    if (OCR2A > 0)
    {
        for (int i = 0; i < AMOUNT_PWM_PINS; i++)
        {
            pin_set_output(pwm_pinsa[i], 1);
        }
    }

    if (OCR2B > 0)
    {
        for (int i = 0; i < AMOUNT_PWM_PINS; i++)
        {

            pin_set_output(pwm_pinsb[i], 1);
        }
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
    cli();
    if (group == PWMGROUP_A)
    {
        if (duty == 0 || duty == 255)
        {
            TIMSK2 &= ~(1 << OCIE2A);

            if (duty == 255)
            {
                for (int i = 0; i < AMOUNT_PWM_PINS; i++)
                {
                    pin_set_output(pwm_pinsa[i], 1);
                }
            }
            else
            {
                for (int i = 0; i < AMOUNT_PWM_PINS; i++)
                {
                    pin_set_output(pwm_pinsa[i], 0);
                }
            }
        }
        else
        {
            TIMSK2 |= (1 << OCIE2A);
        }
        OCR2A = duty;
    }
    else if (group == PWMGROUP_B)
    {
        if (duty == 0 || duty == 255)
        {
            TIMSK2 &= ~(1 << OCIE2B);

            if (duty == 255)
            {
                for (int i = 0; i < AMOUNT_PWM_PINS; i++)
                {
                    pin_set_output(pwm_pinsb[i], 1);
                }
            }
            else
            {
                for (int i = 0; i < AMOUNT_PWM_PINS; i++)
                {
                    pin_set_output(pwm_pinsb[i], 0);
                }
            }
        }
        else
        {
            TIMSK2 |= (1 << OCIE2B);
        }
        OCR2B = duty;
    }
    sei();
}

// zet een pin in een pwm pin groep op plaats i
void pwm_pin_set_group(DigitalPin pin, uint8_t i, PwmGroup group)
{
    cli();
    if (group == PWMGROUP_A)
    {
        pwm_pinsa[i] = pin;
    }
    else if (group == PWMGROUP_B)
    {
        pwm_pinsb[i] = pin;
    }
    sei();
}

// golf led op poort D39 en D41
void pwm_test()
{
    pin_set_mode(MEGA_PIN_D39_DIGITAL, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(MEGA_PIN_D41_DIGITAL, PINMODE_DIGITAL_OUTPUT);

    pwm_pin_set_group(MEGA_PIN_D39_DIGITAL, 0, PWMGROUP_A);
    pwm_pin_set_group(MEGA_PIN_D41_DIGITAL, 0, PWMGROUP_B);

    int counta = 21;
    int countb = 21;
    while (1)
    {
        pwm_group_set_duty(PWMGROUP_A, counta);
        pwm_group_set_duty(PWMGROUP_B, countb);
        counta = (counta + 1) % 255;
        countb = (countb + 10) % 255;
        _delay_ms(10);
    }
}