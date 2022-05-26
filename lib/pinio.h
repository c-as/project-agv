#ifndef _PINIO_H_
#define _PINIO_H_

#include <inttypes.h>

typedef enum
{
    MEGA_PIN_D4,
    MEGA_PIN_D0,
    MEGA_PIN_D1,
    MEGA_PIN_D5,
    MEGA_PIN_D2,
    MEGA_PIN_D3,
    MEGA_PIN_D17,
    MEGA_PIN_D16,
    MEGA_PIN_D6,
    MEGA_PIN_D7,
    MEGA_PIN_D8,
    MEGA_PIN_D9,
    MEGA_PIN_D53,
    MEGA_PIN_D52,
    MEGA_PIN_D51,
    MEGA_PIN_D50,
    MEGA_PIN_D10,
    MEGA_PIN_D11,
    MEGA_PIN_D12,
    MEGA_PIN_D13,
    MEGA_PIN_D49,
    MEGA_PIN_D48,
    MEGA_PIN_D47,
    MEGA_PIN_D46,
    MEGA_PIN_D45,
    MEGA_PIN_D44,
    MEGA_PIN_D43,
    MEGA_PIN_D42,
    MEGA_PIN_D21,
    MEGA_PIN_D20,
    MEGA_PIN_D19,
    MEGA_PIN_D18,
    MEGA_PIN_D38,
    MEGA_PIN_D41,
    MEGA_PIN_D40,
    MEGA_PIN_D37,
    MEGA_PIN_D36,
    MEGA_PIN_D35,
    MEGA_PIN_D34,
    MEGA_PIN_D33,
    MEGA_PIN_D32,
    MEGA_PIN_D31,
    MEGA_PIN_D30,
    MEGA_PIN_D15,
    MEGA_PIN_D14,
    MEGA_PIN_D39,
    MEGA_PIN_D29,
    MEGA_PIN_D28,
    MEGA_PIN_D27,
    MEGA_PIN_D26,
    MEGA_PIN_D25,
    MEGA_PIN_D24,
    MEGA_PIN_D23,
    MEGA_PIN_D22,
    MEGA_PIN_A15,
    MEGA_PIN_A14,
    MEGA_PIN_A13,
    MEGA_PIN_A12,
    MEGA_PIN_A11,
    MEGA_PIN_A10,
    MEGA_PIN_A9,
    MEGA_PIN_A8,
    MEGA_PIN_A7,
    MEGA_PIN_A6,
    MEGA_PIN_A5,
    MEGA_PIN_A4,
    MEGA_PIN_A3,
    MEGA_PIN_A2,
    MEGA_PIN_A1,
    MEGA_PIN_A0,
} MegaPins;

typedef enum
{
    PINMODE_INPUT,
    PINMODE_INPUT_PULLUP,
    PINMODE_OUTPUT,
} PinMode;

typedef struct
{
    uint8_t *pDDR;
    uint8_t *pPIN;
    uint8_t *pPORT;
    uint8_t pin;
} Pin;

Pin get_pin(MegaPins mega_pin);
void pin_set_mode(Pin pin, PinMode mode);
void pin_set_output(Pin pin, bool output);
bool pin_get_input(Pin pin);
void pinio_test();

#endif