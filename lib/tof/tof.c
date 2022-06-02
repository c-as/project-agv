#include <stdio.h>
#include <avr/interrupt.h>
#include "../pinio.h"
#include "vl53l0x-non-arduino/VL53L0X.h"
#include "vl53l0x-non-arduino/util/i2cmaster.h"
#include "vl53l0x-non-arduino/util/millis.h"

#define TIMING_BUDGET_MS 50

void tof_init()
{
    pin_set_mode(MEGA_PIN_D20_DIGITAL, PINMODE_DIGITAL_INPUT_PULLUP);
    pin_set_mode(MEGA_PIN_D22_DIGITAL, PINMODE_DIGITAL_INPUT_PULLUP);

    i2cmaster_init();
    initMillis();
    sei();

    initVL53L0X(1);

    setMeasurementTimingBudget(TIMING_BUDGET_MS * 1000UL);
}

uint16_t tof_measure()
{
    statInfo_t xTraStats;
    uint16_t measurement = readRangeSingleMillimeters(&xTraStats);
    return measurement / 2;
}

void tof_test()
{
    while (1)
    {
        printf("measurement: %i\n", tof_measure());
        if (timeoutOccurred())
        {
            printf("timeout");
        }
    }
}