#include <avr/interrupt.h>
#include "pinio.h"
#include "pwm.h"
#include <util/delay.h>
#include "vec.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

volatile Vec *pwm_groups;
volatile int group_counter = 0;

void pwm_init()
{
    cli();
    TCCR2A = 0;
    TCCR2B = (1 << CS20) | (1 << CS21) | (1 << CS22); // 32 prescaler
    TIMSK2 = (1 << TOIE2);                            // enable compare match interrupt A + overflow
    pwm_groups = vec_new(10);
    sei();
}

ISR(TIMER2_OVF_vect)
{
    // disable compare interrupts
    TIMSK2 &= ~(1 << OCIE0A);

    for (int i = 0; i < pwm_groups->length; i++)
    {
        PwmGroup *group = (PwmGroup *)vec_get((Vec *)pwm_groups, i);

        if (!group)
        {
            printf("pwm error: TIMER2_OVF_INTERRUPT(): failed to get group\n");
            return;
        }

        for (int x = 0; x < group->pins->length; x++)
        {
            DigitalPin *pin = (DigitalPin *)vec_get((Vec *)group->pins, x);

            if (!group)
            {
                printf("pwm error: TIMER2_OVF_INTERRUPT(): failed to get pin from group\n");
                return;
            }

            pin_set_output(*pin, 1);
        }

        if (i == 0)
        {
            TIMSK2 |= (1 << OCIE0A);
            OCR2A = group->duty;
        }
    }
    group_counter = 0;
}

ISR(TIMER2_COMPA_vect)
{
    PwmGroup *group = (PwmGroup *)vec_get((Vec *)pwm_groups, group_counter);

    if (!group)
    {
        printf("pwm error: TIMER2_COMP_INTERRUPT(): failed to get group\n");
        return;
    }

    for (int x = 0; x < group->pins->length; x++)
    {
        DigitalPin *pin = (DigitalPin *)vec_get((Vec *)group->pins, x);

        if (!group)
        {
            printf("pwm error: TIMER2_COMP_INTERRUPT(): failed to get pin from group\n");
            return;
        }

        pin_set_output(*pin, 0);
    }

    if (pwm_groups->length > group_counter + 1)
    {
        PwmGroup *next_group = (PwmGroup *)vec_get((Vec *)pwm_groups, group_counter + 1);

        if (!next_group)
        {
            printf("pwm error: TIMER2_COMP_INTERRUPT(): failed to get next group\n");
            return;
        }

        OCR2A = next_group->duty;
    }
    else
    {
        TIMSK2 &= ~(1 << OCIE0A);
    }

    group_counter++;
}

int pwm_pin_set(DigitalPin pin, uint8_t duty)
{
    cli();
    bool stop = false;

    // check if pin already exists
    for (int i = 0; i < pwm_groups->length; i++)
    {
        if (stop)
        {
            break;
        }

        PwmGroup *group = (PwmGroup *)vec_get((Vec *)pwm_groups, i);

        if (!group)
        {
            printf("pwm error: pwm_pin_set(): failed to get group (check pin)\n");
            sei();
            return 1;
        }

        for (int x = 0; x < group->pins->length; x++)
        {
            DigitalPin *xpin = (DigitalPin *)vec_get((Vec *)group->pins, x);

            if (!xpin)
            {
                printf("pwm error: pwm_pin_set(): failed to get pin from group\n");
                sei();
                return 1;
            }

            // is the pin the same?
            if (xpin->pDDR == pin.pDDR && xpin->pin == pin.pin)
            {
                // check if duty is the same
                if (group->duty == duty)
                {
                    sei();
                    return 0; // pin is already correct
                }
                else
                {
                    if (vec_delete((Vec *)group->pins, x))
                    {
                        printf("pwm error: pwm_pin_set(): removing group pin failed\n");
                        sei();
                        return 1;
                    }

                    // check if group still contains pins
                    if (group->pins->length == 0)
                    {
                        vec_free(group->pins);
                        if (vec_delete((Vec *)pwm_groups, i))
                        {
                            printf("pwm error: pwm_pin_set(): removing group failed\n");
                            sei();
                            return 1;
                        }
                    }
                    stop = true;
                    break;
                }
            }
        }
    }

    if (duty == 0)
    {
        pin_set_output(pin, 0);
        sei();
        return 0;
    }
    else if (duty == 255)
    {
        pin_set_output(pin, 1);
        sei();
        return 0;
    }

    PwmGroup *group = 0;

    // put check if group with duty already exists
    for (int i = 0; i < pwm_groups->length; i++)
    {
        PwmGroup *igroup = (PwmGroup *)vec_get((Vec *)pwm_groups, i);

        if (!igroup)
        {
            printf("pwm error: pwm_pin_set(): failed to get group (duty)\n");
            sei();
            return 1;
        }

        if (igroup->duty == duty)
        {
            group = igroup;
            break;
        }
    }

    int place = 0;

    // get place for group
    if (!group)
    {
        for (int i = 0; i < pwm_groups->length; i++)
        {
            PwmGroup *igroup = (PwmGroup *)vec_get((Vec *)pwm_groups, i);

            if (!igroup)
            {
                printf("pwm error: pwm_pin_set(): failed to get group (place)\n");
                sei();
                return 1;
            }

            if (igroup->duty < duty)
            {
                place = i + 1;
                break;
            }
        }

        // create group
        Vec *vec = vec_new(1);
        if (!vec)
        {
            printf("pwm error: pwm_pin_set(): creating group vec failed\n");
            sei();
            return 1;
        }
        group = malloc(sizeof(PwmGroup));
        if (!group)
        {
            printf("pwm error: pwm_pin_set(): allocating group failed\n");
            sei();
            return 1;
        }

        *group = (PwmGroup){.duty = duty, .pins = vec};
        if (vec_insert((Vec *)pwm_groups, place, group))
        {
            printf("pwm error: pwm_pin_set(): inserting group failed\n");
            sei();
            return 1;
        }
    }

    // insert pin in group
    DigitalPin *ppin = malloc(sizeof(DigitalPin));
    if (!ppin)
    {
        printf("pwm error: pwm_pin_set(): allocating pin failed\n");
        sei();
        return 1;
    }
    *ppin = pin;
    if (vec_append((Vec *)group->pins, ppin))
    {
        printf("pwm error: pwm_pin_set(): appending pin failed\n");
        sei();
        return 1;
    }

    sei();
    return 0;
}

void print_pwm_pins()
{
    printf("all-len:%i\n", pwm_groups->length);
    for (int i = 0; i < pwm_groups->length; i++)
    {
        PwmGroup *group = (PwmGroup *)vec_get((Vec *)pwm_groups, i);

        if (!group)
        {
            printf("pwm error: pwm_test(): failed to get group\n");
            return;
        }

        printf("group-duty:%i\n", group->duty);
        printf("group-len:%i\n", group->pins->length);
        for (int x = 0; x < group->pins->length; x++)
        {
            DigitalPin *xpin = (DigitalPin *)vec_get((Vec *)group->pins, x);

            if (!xpin)
            {
                printf("pwm error: pwm_test(): failed to get pin\n");
                return;
            }

            printf("pin:%i\n", xpin->pin);
        }
    }
}

// golf led op poort D39 en D41
void pwm_test()
{
    pin_set_mode(MEGA_PIN_D39_DIGITAL, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(MEGA_PIN_D41_DIGITAL, PINMODE_DIGITAL_OUTPUT);

    int val = 1;

    while (1)
    {
        printf("%i\n", val);
        pwm_pin_set(MEGA_PIN_D39_DIGITAL, val++);
    }
}