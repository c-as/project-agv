#ifndef _NAVIGATIE_H
#define _NAVIGATIE_H

DigitalPin rijrichting_tof(RijRichting richting);
int agv_muur_afstand(RijRichting richting, int afstand_mm);
int agv_muren_midden(RijRichting ene_kant);
void agv_zet_vooruit();
void agv_zet_recht(RijRichting probe_muur);
int agv_volg_rand_target(RijRichting volg_muur, RijRichting target_muur, uint16_t target_afstand_mm);
void baan_wisselen();
void agv_start_positie();
void agv_start_navigatie();

#endif