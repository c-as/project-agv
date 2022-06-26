#include <avr/io.h>
#include <avr/interrupt.h>
#include "motoren.h"
#include "pinio.h"
#include "pwm.h"
#include "time.h"

#define PIN_IN1_MOTOR1 MEGA_PIN_D8_DIGITAL
#define PIN_IN2_MOTOR1 MEGA_PIN_D9_DIGITAL
#define PIN_IN1_MOTOR2 MEGA_PIN_D6_DIGITAL
#define PIN_IN2_MOTOR2 MEGA_PIN_D7_DIGITAL
#define PIN_IN1_MOTOR3 MEGA_PIN_D4_DIGITAL
#define PIN_IN2_MOTOR3 MEGA_PIN_D5_DIGITAL
#define PIN_IN1_MOTOR4 MEGA_PIN_D2_DIGITAL
#define PIN_IN2_MOTOR4 MEGA_PIN_D3_DIGITAL
#define MOTOREN_PWM_GROUP PWMGROUP_A

void motoren_init()
{
    pin_set_mode(PIN_IN1_MOTOR1, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN2_MOTOR1, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN1_MOTOR2, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN2_MOTOR2, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN1_MOTOR3, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN2_MOTOR3, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN1_MOTOR4, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN2_MOTOR4, PINMODE_DIGITAL_OUTPUT);

    current_duty = 0;
    current_rijrichting = 0;
}

void motor_zet_richting(int motor, MotorRichting kant)
{
    cli();
    if (kant == MOTORRICHTING_CW)
    {
        switch (motor)
        {
        case 1:
            pwm_pin_set_group(PIN_IN2_MOTOR1, 0, MOTOREN_PWM_GROUP);
            pin_set_output(PIN_IN1_MOTOR1, 0);
            break;
        case 2:
            pwm_pin_set_group(PIN_IN2_MOTOR2, 1, MOTOREN_PWM_GROUP);
            pin_set_output(PIN_IN1_MOTOR2, 0);
            break;
        case 3:
            pwm_pin_set_group(PIN_IN2_MOTOR3, 2, MOTOREN_PWM_GROUP);
            pin_set_output(PIN_IN1_MOTOR3, 0);
            break;
        case 4:
            pwm_pin_set_group(PIN_IN1_MOTOR4, 3, MOTOREN_PWM_GROUP);
            pin_set_output(PIN_IN2_MOTOR4, 0);
            break;
        }
    }
    else if (kant == MOTORRICHTING_CCW)
    {
        switch (motor)
        {
        case 1:
            pwm_pin_set_group(PIN_IN1_MOTOR1, 0, MOTOREN_PWM_GROUP);
            pin_set_output(PIN_IN2_MOTOR1, 0);
            break;
        case 2:
            pwm_pin_set_group(PIN_IN1_MOTOR2, 1, MOTOREN_PWM_GROUP);
            pin_set_output(PIN_IN2_MOTOR2, 0);
            break;
        case 3:
            pwm_pin_set_group(PIN_IN1_MOTOR3, 2, MOTOREN_PWM_GROUP);
            pin_set_output(PIN_IN2_MOTOR3, 0);
            break;
        case 4:
            pwm_pin_set_group(PIN_IN2_MOTOR4, 3, MOTOREN_PWM_GROUP);
            pin_set_output(PIN_IN1_MOTOR4, 0);
            break;
        }
    }
    sei();
}

void motor_zet_duty(uint8_t duty)
{
    pwm_group_set_duty(MOTOREN_PWM_GROUP, duty);
    current_duty = duty;
}

void rijden(RijRichting kant, uint8_t duty)
{
    if (kant == RIJRICHTING_VOORUIT)
    {
        motor_zet_richting(1, MOTORRICHTING_CCW);
        motor_zet_richting(2, MOTORRICHTING_CW);
        motor_zet_richting(3, MOTORRICHTING_CCW);
        motor_zet_richting(4, MOTORRICHTING_CW);
    }
    else if (kant == RIJRICHTING_ACHTERUIT)
    {
        motor_zet_richting(1, MOTORRICHTING_CW);
        motor_zet_richting(2, MOTORRICHTING_CCW);
        motor_zet_richting(3, MOTORRICHTING_CW);
        motor_zet_richting(4, MOTORRICHTING_CCW);
    }
    else if (kant == RIJRICHTING_LINKS)
    {
        motor_zet_richting(1, MOTORRICHTING_CW);
        motor_zet_richting(2, MOTORRICHTING_CW);
        motor_zet_richting(3, MOTORRICHTING_CCW);
        motor_zet_richting(4, MOTORRICHTING_CCW);
    }
    else if (kant == RIJRICHTING_RECHTS)
    {
        motor_zet_richting(1, MOTORRICHTING_CCW);
        motor_zet_richting(2, MOTORRICHTING_CCW);
        motor_zet_richting(3, MOTORRICHTING_CW);
        motor_zet_richting(4, MOTORRICHTING_CW);
    }
    else if (kant == RIJRICHTING_CW)
    {
        motor_zet_richting(1, MOTORRICHTING_CCW);
        motor_zet_richting(2, MOTORRICHTING_CCW);
        motor_zet_richting(3, MOTORRICHTING_CCW);
        motor_zet_richting(4, MOTORRICHTING_CCW);
    }
    else if (kant == RIJRICHTING_CCW)
    {
        motor_zet_richting(1, MOTORRICHTING_CW);
        motor_zet_richting(2, MOTORRICHTING_CW);
        motor_zet_richting(3, MOTORRICHTING_CW);
        motor_zet_richting(4, MOTORRICHTING_CW);
    }
    // eerst beginnen met draaien daarna zachter
    if (current_duty == 0)
    {
        motor_zet_duty(UINT8_MAX);
        wacht_millis(100);
    }

    motor_zet_duty(duty);

    current_rijrichting = kant;
}

void rijden_stop()
{
    motor_zet_duty(0);
}

void motoren_test()
{
    while (1)
    {
        rijden(RIJRICHTING_CW, UINT8_MAX);
        wacht_millis(500);
        rijden(RIJRICHTING_CCW, UINT8_MAX);
        wacht_millis(500);
        rijden(RIJRICHTING_VOORUIT, UINT8_MAX);
        wacht_millis(500);
        rijden(RIJRICHTING_ACHTERUIT, UINT8_MAX);
        wacht_millis(500);
        rijden(RIJRICHTING_LINKS, UINT8_MAX);
        wacht_millis(500);
        rijden(RIJRICHTING_RECHTS, UINT8_MAX);
        wacht_millis(500);
    }
}