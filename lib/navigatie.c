#include <inttypes.h>
#include "pinio.h"
#include "tof/tof.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "motoren.h"

#define SNELHEID_VOOR 90
#define SNELHEID_ZIJ 110
#define MARGE 20

RijRichting rijrichting_tegenovergesteld(RijRichting ene_kant)
{
    switch (ene_kant)
    {
    case RIJRICHTING_VOORUIT:
        return RIJRICHTING_ACHTERUIT;
    case RIJRICHTING_ACHTERUIT:
        return RIJRICHTING_VOORUIT;
    case RIJRICHTING_RECHTS:
        return RIJRICHTING_LINKS;
    case RIJRICHTING_LINKS:
        return RIJRICHTING_RECHTS;
    default:
        printf("navigatie.c error: agv_houd_midden(): incorrecte richting\n");
        return -1;
    }
}

// Converteer een motoren.h rijrichting naar tof sensor poort
DigitalPin rijrichting_tof(RijRichting richting)
{
    switch (richting)
    {
    case RIJRICHTING_VOORUIT:
        return TOF_VOOR;
        break;
    case RIJRICHTING_ACHTERUIT:
        return TOF_ACHTER;
        break;
    case RIJRICHTING_RECHTS:
        return TOF_RECHTS;
        break;
    case RIJRICHTING_LINKS:
        return TOF_LINKS;
        break;
    default:
        printf("navigatie.c error: rijrichting_tof(): incorrecte richting\n");
        return (DigitalPin){.pDDR = 0, .pPIN = 0, .pPORT = 0, .pin = 0};
    }
}

int rijrichting_snelheid(RijRichting richting)
{
    switch (richting)
    {
    case RIJRICHTING_VOORUIT:
        return SNELHEID_VOOR;
        break;
    case RIJRICHTING_ACHTERUIT:
        return SNELHEID_VOOR;
        break;
    case RIJRICHTING_RECHTS:
        return SNELHEID_ZIJ;
        break;
    case RIJRICHTING_LINKS:
        return SNELHEID_ZIJ;
        break;
    default:
        printf("navigatie.c error: rijrichting_tof(): incorrecte richting\n");
        return 0;
    }
}

int agv_volg_rand(RijRichting rand_richting, RijRichting target_richting, uint16_t target_afstand)
{
    DigitalPin tof_rand = rijrichting_tof(rand_richting);
    DigitalPin tof_target = rijrichting_tof(target_richting);

    int snelheid_rand = rijrichting_snelheid(rand_richting);
    int snelheid_target = rijrichting_snelheid(target_richting);

    if (!tof_rand.pin || !tof_target.pin)
    {
        printf("navigatie.c error: agv_volg_rand(): geen tof\n");
        return 1;
    }

    uint16_t rand_afstand = tof_measure(tof_rand);
    while (1)
    {
        uint16_t meting_rand = tof_measure(tof_rand);

        if (abs(meting_rand - rand_afstand) < MARGE)
        {
            uint16_t meting_target = tof_measure(tof_target);

            if (abs(meting_target - target_afstand) < MARGE)
            {
                rijden_stop();
                return 0;
            }
            else if (meting_target > target_afstand)
            {
                rijden(target_richting, snelheid_target);
            }
            else if (meting_target < target_afstand)
            {
                rijden(rijrichting_tegenovergesteld(target_richting), snelheid_target);
            }
        }
        else if (meting_rand > rand_afstand)
        {
            rijden(rand_richting, snelheid_rand);
        }
        else if (meting_rand < rand_afstand)
        {
            rijden(rijrichting_tegenovergesteld(rand_richting), snelheid_rand);
        }
    }
}

int agv_naar_rand(RijRichting rand_richting, uint16_t target_afstand)
{
    DigitalPin tof_rand = rijrichting_tof(rand_richting);

    int snelheid_rand = rijrichting_snelheid(rand_richting);

    if (!tof_rand.pin)
    {
        printf("navigatie.c error: agv_naar_rand(): geen tof\n");
        return 1;
    }

    while (1)
    {
        uint16_t meting_rand = tof_measure(tof_rand);

        if (abs(meting_rand - target_afstand) < MARGE)
        {
            rijden_stop();
            return 0;
        }
        else if (meting_rand > target_afstand)
        {
            rijden(rand_richting, snelheid_rand);
        }
        else if (meting_rand < target_afstand)
        {
            rijden(rijrichting_tegenovergesteld(rand_richting), snelheid_rand);
        }
    }
}

void agv_start_navigatie()
{
    while (1)
    {
        agv_naar_rand(RIJRICHTING_VOORUIT, 100);
        wacht_millis(2000);
        agv_naar_rand(RIJRICHTING_ACHTERUIT, 100);
        wacht_millis(2000);
    }
}