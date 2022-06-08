#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../pinio.h"
#include "vl53l0x-non-arduino/VL53L0X.h"
#include "vl53l0x-non-arduino/util/i2cmaster.h"
#include "vl53l0x-non-arduino/util/millis.h"
#include "tof.h"

#define TIMING_BUDGET_MS 50

void tof_init()
{
    i2cmaster_init();
    initMillis();
    sei();
}

uint16_t tof_measure(DigitalPin tof_x_pin)
{
    // zet de pin laag
    pin_set_mode(tof_x_pin, PINMODE_DIGITAL_OUTPUT);

    initVL53L0X(1);
    setMeasurementTimingBudget(TIMING_BUDGET_MS * 1000UL);

    statInfo_t xTraStats;
    uint16_t measurement = readRangeSingleMillimeters(&xTraStats);

    // zet de pin weer hoog
    pin_set_mode(tof_x_pin, PINMODE_DIGITAL_INPUT_PULLUP);

    return measurement / 2;
}

void tof_test()
{
    while (1)
    {
        printf("measurement tof 1: %i\n", tof_measure(TOF_1_PIN_X));
        printf("measurement tof 2: ------> %i\n", tof_measure(TOF_2_PIN_X));
        printf("measurement tof 3: ------------> %i\n", tof_measure(TOF_3_PIN_X));
        printf("measurement tof 4: ------------------> %i\n", tof_measure(TOF_4_PIN_X));
    }
}