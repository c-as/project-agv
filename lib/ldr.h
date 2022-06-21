#ifndef _LDR_H_
#define _LDR_H_

#define PIN_LDR1 MEGA_PIN_A8_ANALOG
#define PIN_LDR2 MEGA_PIN_A10_ANALOG
#define PIN_LDR3 MEGA_PIN_A12_ANALOG
#define PIN_LDR4 MEGA_PIN_A14_ANALOG

void ldr_vergelijken();
void ldr_volgen();
void ldr_check();

#endif