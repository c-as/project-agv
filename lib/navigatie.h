#ifndef _NAVIGATIE_H_
#define _NAVIGATIE_H_

#include <inttypes.h>
#include "motoren.h"
#include "pinio.h"

RijRichting rijrichting_tegenovergesteld(RijRichting ene_kant);
DigitalPin rijrichting_tof(RijRichting richting);
int rijrichting_snelheid(RijRichting richting);
int agv_volg_rand(RijRichting rand_richting, RijRichting target_richting, uint16_t target_afstand);
int agv_naar_rand(RijRichting rand_richting, uint16_t target_afstand);
void agv_start_navigatie();

#endif