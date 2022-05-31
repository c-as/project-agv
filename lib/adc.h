#ifndef _ADC_H_
#define _ADC_H_

#define MEGA_PIN_A0_ANALOG \
    (AnalogPin) { .mux2 = 0, .mux5 = 0 }
#define MEGA_PIN_A1_ANALOG \
    (AnalogPin) { .mux2 = 1, .mux5 = 0 }
#define MEGA_PIN_A2_ANALOG \
    (AnalogPin) { .mux2 = 2, .mux5 = 0 }
#define MEGA_PIN_A3_ANALOG \
    (AnalogPin) { .mux2 = 3, .mux5 = 0 }
#define MEGA_PIN_A4_ANALOG \
    (AnalogPin) { .mux2 = 4, .mux5 = 0 }
#define MEGA_PIN_A5_ANALOG \
    (AnalogPin) { .mux2 = 5, .mux5 = 0 }
#define MEGA_PIN_A6_ANALOG \
    (AnalogPin) { .mux2 = 6, .mux5 = 0 }
#define MEGA_PIN_A7_ANALOG \
    (AnalogPin) { .mux2 = 7, .mux5 = 0 }
#define MEGA_PIN_A8_ANALOG \
    (AnalogPin) { .mux2 = 0, .mux5 = 1 }
#define MEGA_PIN_A9_ANALOG \
    (AnalogPin) { .mux2 = 1, .mux5 = 1 }
#define MEGA_PIN_A10_ANALOG \
    (AnalogPin) { .mux2 = 2, .mux5 = 1 }
#define MEGA_PIN_A11_ANALOG \
    (AnalogPin) { .mux2 = 3, .mux5 = 1 }
#define MEGA_PIN_A12_ANALOG \
    (AnalogPin) { .mux2 = 4, .mux5 = 1 }
#define MEGA_PIN_A13_ANALOG \
    (AnalogPin) { .mux2 = 5, .mux5 = 1 }
#define MEGA_PIN_A14_ANALOG \
    (AnalogPin) { .mux2 = 6, .mux5 = 1 }
#define MEGA_PIN_A15_ANALOG \
    (AnalogPin) { .mux2 = 7, .mux5 = 1 }

typedef struct // pakket van data voor het gebruik van een specifieke analoge pin
{
    volatile uint8_t mux2;
    volatile uint8_t mux5;
} AnalogPin;

void adc_init();
uint16_t adc_convert(AnalogPin pin);
void adc_test();

#endif