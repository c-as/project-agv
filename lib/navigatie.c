#include <stdlib.h>
#include <avr/io.h>
#include "tof/tof.h"
#include "motoren.h"
#include <stdio.h>
#include <avr/delay.h>

#define VOORUIT_DIFF_MM 50
#define MUUR_DIFF_MM 5
#define DUTY_MUUR 100
#define TARGET_STAP_MM 20
#define RECHT_DIFF_MM 2
#define VOLG_DIFF_MM 2
#define SNELHEID 8

RijRichting rijrichting_omgedraaid(RijRichting ene_kant)
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

// agv probeert afstand te verkrijgen met gegeven muur
// werkt alleen als tof recht staat
int agv_muur_afstand(RijRichting richting, int afstand_mm)
{
    DigitalPin tof = rijrichting_tof(richting);

    if (!tof.pin)
    {
        printf("navigatie.c error: agv_muur_afstand(): geen tof\n");
        return 1;
    }

    uint16_t meting = tof_measure(tof);
    while (abs(meting - afstand_mm) > MUUR_DIFF_MM)
    {
        switch (richting)
        {
        case RIJRICHTING_VOORUIT:
            if (meting > afstand_mm)
                rijden(RIJRICHTING_VOORUIT, DUTY_MUUR);
            else
                rijden(RIJRICHTING_ACHTERUIT, DUTY_MUUR);
            break;
        case RIJRICHTING_ACHTERUIT:
            if (meting > afstand_mm)
                rijden(RIJRICHTING_ACHTERUIT, DUTY_MUUR);
            else
                rijden(RIJRICHTING_VOORUIT, DUTY_MUUR);
            break;
        case RIJRICHTING_RECHTS:
            if (meting > afstand_mm)
                rijden(RIJRICHTING_RECHTS, DUTY_MUUR);
            else
                rijden(RIJRICHTING_LINKS, DUTY_MUUR);
            break;
        case RIJRICHTING_LINKS:
            if (meting > afstand_mm)
                rijden(RIJRICHTING_LINKS, DUTY_MUUR);
            else
                rijden(RIJRICHTING_RECHTS, DUTY_MUUR);
            break;
        default:
            break;
        }
    }

    rijden_stop();

    return 0;
}

// agv probeert in het midden tussen 2 muren te komen
// werkt alleen als agv recht staat en muren parallel
int agv_muren_midden(RijRichting ene_kant)
{
    RijRichting andere_kant = rijrichting_omgedraaid(ene_kant);

    uint16_t meting_ene_kant = tof_measure(rijrichting_tof(ene_kant));
    uint16_t meting_andere_kant = tof_measure(rijrichting_tof(andere_kant));

    agv_muur_afstand(ene_kant, (meting_ene_kant + meting_andere_kant) / 2);
    return 0;
}

// zet agv ongeveer vooruit met de voorkant in de richting van een pad
void agv_zet_vooruit()
{
    uint16_t meting_voor = tof_measure(TOF_X_PLUS);
    uint16_t meting_rechts = tof_measure(TOF_Y_MIN);
    uint16_t meting_links = tof_measure(TOF_Y_PLUS);

    // draai net zo lang todat tof voor de grootste afstand meet
    rijden(RIJRICHTING_CW, 50);

    while (1)
    {
        int diff_rechts = meting_voor - meting_rechts;
        int diff_links = meting_voor - meting_links;

        if (diff_rechts > VOORUIT_DIFF_MM && diff_links > VOORUIT_DIFF_MM)
        {
            break;
        }
    }

    rijden_stop();
}

// zet agv parallel met muur
// werkt alleen als agv al ongeveer recht staat (+- 45 graden)
void agv_zet_recht(RijRichting probe_muur)
{
    DigitalPin tof = rijrichting_tof(probe_muur);

    uint16_t meting = tof_measure(tof);

    // draai super sloom
    rijden(RIJRICHTING_CW, 100);

    int last_diff = 0;

    // als het goed is wordt het verschil nu alleen maar kleiner totdat de agv recht staat
    while (1)
    {
        int diff = meting - tof_measure(tof);

        if (diff > last_diff)
        {
            return;
        }

        last_diff = diff;
    }

    rijden_stop();
}

void tof_afstanden()
{
    printf("tof 1...\n");
    printf("measurement tof 1: %i\n", tof_measure(TOF_1_PIN_X));
    printf("tof 2...\n");
    printf("measurement tof 2: ------> %i\n", tof_measure(TOF_2_PIN_X));
    printf("tof 3...\n");
    printf("measurement tof 3: ------------> %i\n", tof_measure(TOF_3_PIN_X));
    printf("tof 4...\n");
    printf("measurement tof 4: ------------------> %i\n", tof_measure(TOF_4_PIN_X));
}

#define AFSTANDHEK 100
#define BWSNELHEID 150
void baan_wisselen()
{
    _delay_ms(1000);
    tof_afstanden();
    while (tof_measure(TOF_1_PIN_X) > AFSTANDHEK)
    {
        rijden(RIJRICHTING_X_PLUS, BWSNELHEID);
    }
    rijden_stop();
    if (tof_measure(TOF_1_PIN_X) < AFSTANDHEK)
    {
        tof_afstanden();
        rijden_stop();
        _delay_ms(1000);
        uint16_t x = tof_measure(TOF_4_PIN_X);
        while (tof_measure(TOF_2_PIN_X) < 200)
        {
            rijden(RIJRICHTING_Y_PLUS, BWSNELHEID);
        }
        tof_afstanden();
        rijden_stop();
        uint16_t TOF2Prev = tof_measure(TOF_2_PIN_X);
        _delay_ms(1000);
        uint16_t y = tof_measure(TOF_4_PIN_X);
        while (tof_measure(TOF_2_PIN_X) > (TOF2Prev + 20))
        {
            rijden(RIJRICHTING_Y_PLUS, BWSNELHEID);
        }
        tof_afstanden();
        rijden_stop();
        _delay_ms(1000);
        uint16_t z = y - x;
        uint16_t zdist = z + tof_measure(TOF_4_PIN_X);
        while (zdist < tof_measure(TOF_4_PIN_X))
        {
            rijden(RIJRICHTING_Y_PLUS, BWSNELHEID);
        }
        tof_afstanden();
        rijden_stop();
        _delay_ms(1000);
        while (tof_measure(TOF_4_PIN_X) > 200)
        {
            rijden(RIJRICHTING_X_MIN, BWSNELHEID);
        }
        tof_afstanden();
        rijden_stop();
    }
}

void agv_start_positie()
{
    agv_zet_vooruit();
    agv_zet_recht(RIJRICHTING_RECHTS);
    agv_muur_afstand(RIJRICHTING_ACHTERUIT, 10);
    agv_muur_afstand(RIJRICHTING_LINKS, 10);
}

int agv_volg_rand(RijRichting rand_richting, RijRichting target_richting, uint16_t target_afstand)
{
    DigitalPin tof_rand = rijrichting_tof(rand_richting);
    DigitalPin tof_target = rijrichting_tof(target_richting);

    if (!tof_rand.pin || !tof_target.pin)
    {
        printf("navigatie.c error: agv_volg_rand(): geen tof\n");
        return 1;
    }

    uint16_t rand_afstand = tof_measure(tof_rand);
    int marge = 10;
    while (1)
    {
        uint16_t meting_rand = tof_measure(tof_rand);

        if (abs(meting_rand - rand_afstand) < marge)
        {
            uint16_t meting_target = tof_measure(tof_target);

            if (abs(meting_target - target_afstand) < marge)
            {
                rijden_stop();
                return 0;
            }
            else if (meting_target > target_afstand)
            {
                rijden(target_richting, SNELHEID);
            }
            else if (meting_target < target_afstand)
            {
                rijden(rijrichting_omgedraaid(target_richting), SNELHEID);
            }
        }
        else if (meting_rand > rand_afstand)
        {
            rijden(rand_richting, SNELHEID);
        }
        else if (meting_rand < rand_afstand)
        {
            rijden(rijrichting_omgedraaid(rand_richting), SNELHEID);
        }
    }
    //baan_wisselen();
}

void agv_start_navigatie()
{
    agv_volg_rand(RIJRICHTING_TOF_3, RIJRICHTING_TOF_1, 100);
}
