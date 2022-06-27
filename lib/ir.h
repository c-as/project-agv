#ifndef _IR_H_
#define _IR_H_

#include <stdbool.h>

volatile bool ir_1_enabled;
volatile bool ir_2_enabled;

#define IR_LINKS_ENABLED ir_1_enabled
#define IR_RECHTS_ENABLED ir_2_enabled

void ir_init();
void ir_check();

#endif