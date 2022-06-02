#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "pinio.h"

#define AMOUNT_PWM_PINS 4

DigitalPin pwm_pinsa[AMOUNT_PWM_PINS];
DigitalPin pwm_pinsb[AMOUNT_PWM_PINS];

void pinio_init()
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

void pin_set_mode(DigitalPin pin, DigitalPinMode mode)
{
    switch (mode)
    {
    case PINMODE_DIGITAL_INPUT:
        *pin.pDDR &= ~(1 << pin.pin);
        *pin.pPORT &= ~(1 << pin.pin);
        break;
    case PINMODE_DIGITAL_INPUT_PULLUP:
        *pin.pDDR &= ~(1 << pin.pin);
        *pin.pPORT |= (1 << pin.pin); // om de interne pullup weerstand te gebruiken moet de port hoog gezet worden
        break;
    case PINMODE_DIGITAL_OUTPUT:
        *pin.pDDR |= (1 << pin.pin);
        *pin.pPORT &= ~(1 << pin.pin);
        break;
    }
}

// zet de pin hoog(1) of laag(0)
void pin_set_output(DigitalPin pin, bool output)
{
    if (output)
        *pin.pPORT |= (1 << pin.pin);
    else
        *pin.pPORT &= ~(1 << pin.pin);
}

// zet de duty cycle van een pwm pins groep
void group_set_pwm(PwmGroup group, uint8_t duty)
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
void pin_set_pwm_group(DigitalPin pin, uint8_t i, PwmGroup group)
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

// zet een pin in de lijst van van een groep pwm pins op plek i met een duty cycle (van de groep)
void pin_set_pwm(DigitalPin pin, uint8_t i, PwmGroup group, uint8_t duty)
{
    pin_set_pwm_group(pin, i, group);
    group_set_pwm(group, duty);
}

// kijk of pin hoog(1) of laag(0) is
bool pin_get_input(DigitalPin pin)
{
    if (*pin.pPORT & (1 << pin.pin))          // kijk of de interne pullup weerstand wordt gebruikt
        return !(*pin.pPIN & (1 << pin.pin)); // als dat zo is dan moet de waarde omgedraaid worden
    else
        return *pin.pPIN & (1 << pin.pin);
}

// knipper led op poort A12
void pinio_test_digital()
{
    pin_set_mode(MEGA_PIN_A12_DIGITAL, PINMODE_DIGITAL_OUTPUT);

    while (1)
    {
        pin_set_output(MEGA_PIN_A12_DIGITAL, 0);
        _delay_ms(500);
        pin_set_output(MEGA_PIN_A12_DIGITAL, 1);
        _delay_ms(500);
    }
}

// golf led op poort D39 en D41
void pinio_test_pwm()
{
    pin_set_mode(MEGA_PIN_D39_DIGITAL, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(MEGA_PIN_D41_DIGITAL, PINMODE_DIGITAL_OUTPUT);

    int counta = 21;
    int countb = 21;
    while (1)
    {
        pin_set_pwm(MEGA_PIN_D39_DIGITAL, 0, PWMGROUP_A, counta);
        pin_set_pwm(MEGA_PIN_D41_DIGITAL, 0, PWMGROUP_B, countb);
        counta = (counta + 1) % 255;
        countb = (countb + 20) % 255;
        _delay_ms(10);
    }
}