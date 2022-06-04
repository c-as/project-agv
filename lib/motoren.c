#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "motoren.h"
#include "pinio.h"

#define PIN_IN1_MOTOR1 MEGA_PIN_D8_DIGITAL
#define PIN_IN2_MOTOR1 MEGA_PIN_D9_DIGITAL
#define PIN_IN1_MOTOR2 MEGA_PIN_D6_DIGITAL
#define PIN_IN2_MOTOR2 MEGA_PIN_D7_DIGITAL
#define PIN_IN1_MOTOR3 MEGA_PIN_D4_DIGITAL
#define PIN_IN2_MOTOR3 MEGA_PIN_D5_DIGITAL
#define PIN_IN1_MOTOR4 MEGA_PIN_D2_DIGITAL
#define PIN_IN2_MOTOR4 MEGA_PIN_D3_DIGITAL

void init_motoren()
{
    pin_set_mode(PIN_IN1_MOTOR1, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN2_MOTOR1, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN1_MOTOR2, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN2_MOTOR2, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN1_MOTOR3, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN2_MOTOR3, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN1_MOTOR4, PINMODE_DIGITAL_OUTPUT);
    pin_set_mode(PIN_IN2_MOTOR4, PINMODE_DIGITAL_OUTPUT);
}

void motor(int motor, MotorRichting kant)
{
    if (kant == MOTORRICHTING_CW)
    {
        switch (motor)
        {
        case 1:
            pin_set_output(PIN_IN1_MOTOR1, 0);
            pin_set_output(PIN_IN2_MOTOR1, 1);
            break;
        case 2:
            pin_set_output(PIN_IN1_MOTOR2, 0);
            pin_set_output(PIN_IN2_MOTOR2, 1);
            break;
        case 3:
            pin_set_output(PIN_IN1_MOTOR3, 0);
            pin_set_output(PIN_IN2_MOTOR3, 1);
            break;
        case 4:
            pin_set_output(PIN_IN1_MOTOR4, 1);
            pin_set_output(PIN_IN2_MOTOR4, 0);
            break;
        }
    }
    else if (kant == MOTORRICHTING_CCW)
    {
        switch (motor)
        {
        case 1:
            pin_set_output(PIN_IN1_MOTOR1, 1);
            pin_set_output(PIN_IN2_MOTOR1, 0);
            break;
        case 2:
            pin_set_output(PIN_IN1_MOTOR2, 1);
            pin_set_output(PIN_IN2_MOTOR2, 0);
            break;
        case 3:
            pin_set_output(PIN_IN1_MOTOR3, 1);
            pin_set_output(PIN_IN2_MOTOR3, 0);
            break;
        case 4:
            pin_set_output(PIN_IN1_MOTOR4, 0);
            pin_set_output(PIN_IN2_MOTOR4, 1);
            break;
        }
    }
    else if (kant == MOTORRICHTING_STOP)
    {
        switch (motor)
        {
        case 1:
            pin_set_output(PIN_IN1_MOTOR1, 0);
            pin_set_output(PIN_IN2_MOTOR1, 0);
            break;
        case 2:
            pin_set_output(PIN_IN1_MOTOR2, 0);
            pin_set_output(PIN_IN2_MOTOR2, 0);
            break;
        case 3:
            pin_set_output(PIN_IN1_MOTOR3, 0);
            pin_set_output(PIN_IN2_MOTOR3, 0);
            break;
        case 4:
            pin_set_output(PIN_IN1_MOTOR4, 0);
            pin_set_output(PIN_IN2_MOTOR4, 0);
            break;
        }
    }
}

void rijden(RijRichting kant)
{
    if (kant == RIJRICHTING_VOORUIT || kant == RIJRICHTING_X_PLUS)
    {
        motor(1, MOTORRICHTING_CCW);
        motor(2, MOTORRICHTING_CW);
        motor(3, MOTORRICHTING_CCW);
        motor(4, MOTORRICHTING_CW);
    }
    else if (kant == RIJRICHTING_ACHTERUIT || kant == RIJRICHTING_X_MIN)
    {
        motor(1, MOTORRICHTING_CW);
        motor(2, MOTORRICHTING_CCW);
        motor(3, MOTORRICHTING_CW);
        motor(4, MOTORRICHTING_CCW);
    }
    else if (kant == RIJRICHTING_LINKS || kant == RIJRICHTING_Y_PLUS)
    {
        motor(1, MOTORRICHTING_CW);
        motor(2, MOTORRICHTING_CW);
        motor(3, MOTORRICHTING_CCW);
        motor(4, MOTORRICHTING_CCW);
    }
    else if (kant == RIJRICHTING_RECHTS || kant == RIJRICHTING_Y_MIN)
    {
        motor(1, MOTORRICHTING_CCW);
        motor(2, MOTORRICHTING_CCW);
        motor(3, MOTORRICHTING_CW);
        motor(4, MOTORRICHTING_CW);
    }
    else if (kant == RIJRICHTING_CW)
    {
        motor(1, MOTORRICHTING_CCW);
        motor(2, MOTORRICHTING_CCW);
        motor(3, MOTORRICHTING_CCW);
        motor(4, MOTORRICHTING_CCW);
    }
    else if (kant == RIJRICHTING_CCW)
    {
        motor(1, MOTORRICHTING_CW);
        motor(2, MOTORRICHTING_CW);
        motor(3, MOTORRICHTING_CW);
        motor(4, MOTORRICHTING_CW);
    }
    else if (kant == RIJRICHTING_STOP)
    {
        motor(1, MOTORRICHTING_STOP);
        motor(2, MOTORRICHTING_STOP);
        motor(3, MOTORRICHTING_STOP);
        motor(4, MOTORRICHTING_STOP);
    }
}

void motoren_test()
{
    while (1)
    {
        rijden(RIJRICHTING_CW);
        _delay_ms(500);
        rijden(RIJRICHTING_CCW);
        _delay_ms(500);
        rijden(RIJRICHTING_VOORUIT);
        _delay_ms(500);
        rijden(RIJRICHTING_ACHTERUIT);
        _delay_ms(500);
        rijden(RIJRICHTING_LINKS);
        _delay_ms(500);
        rijden(RIJRICHTING_RECHTS);
        _delay_ms(500);
    }
}