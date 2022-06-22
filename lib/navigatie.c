#include <stdlib.h>
#include <avr/io.h>
#include "tof/tof.h"
#include "motoren.h"
#include <stdio.h>

#define VOORUIT_DIFF_MM 50
#define MUUR_DIFF_MM 2
#define DUTY_MUUR 255
#define TARGET_STAP_MM 20

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
    RijRichting andere_kant;
    switch (ene_kant)
    {
    case RIJRICHTING_VOORUIT:
        andere_kant = RIJRICHTING_ACHTERUIT;
        break;
    case RIJRICHTING_ACHTERUIT:
        andere_kant = RIJRICHTING_VOORUIT;
        break;
    case RIJRICHTING_RECHTS:
        andere_kant = RIJRICHTING_LINKS;
        break;
    case RIJRICHTING_LINKS:
        andere_kant = RIJRICHTING_RECHTS;
        break;
    default:
        printf("navigatie.c error: agv_houd_midden(): incorrecte richting\n");
        return 1;
    }

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

// agv probeert op staande afstand rand te volgen om een target afstand op een andere muur te verkrijgen
int agv_volg_rand_target(RijRichting volg_muur, RijRichting target_muur, uint16_t target_afstand_mm)
{
    DigitalPin tof_volg = rijrichting_tof(volg_muur);
    DigitalPin tof_target = rijrichting_tof(target_muur);
    if (!tof_volg.pin || !tof_target.pin)
    {
        printf("navigatie.c error: agv_muur_afstand(): geen tof\n");
        return 1;
    }

    uint16_t volg_afstand = tof_measure(tof_volg);
    uint16_t meting_target = tof_measure(tof_target);
    while (abs(meting_target - target_afstand_mm) > MUUR_DIFF_MM)
    {
        agv_zet_recht(volg_muur);

        if (meting_target < target_afstand_mm)
            agv_muur_afstand(target_muur, meting_target - TARGET_STAP_MM);
        else
            agv_muur_afstand(target_muur, meting_target + TARGET_STAP_MM);

        agv_muur_afstand(volg_muur, volg_afstand);

        volg_afstand = tof_measure(tof_volg);
        meting_target = tof_measure(tof_target);
    }

    return 0;
}

void baan_wisselen()
{
    // ToF 1/2 < 170
    if (tof_measure(TOF_1_PIN_X) < 170)
    {
        /// ToF 1, 2 & 4 uitlezen (X)
        uint16_t X = tof_measure(TOF_4_PIN_X);
        rijden(RIJRICHTING_Y_PLUS, UINT8_MAX);
        // ToF 1 < 2
        if (tof_measure(TOF_1_PIN_X) < tof_measure(TOF_2_PIN_X))
        {
            /// ToF 2 uitlezen
            // ToF 2 < 30
            if (tof_measure(TOF_2_PIN_X) < 40)
            {
                /// ToF 4 uitlezen (Y)
                uint16_t Y1 = tof_measure(TOF_4_PIN_X);
                /// afstand Z = Y-X
                uint16_t Z1 = Y1 - X;
                //  ToF 1 > 30
                if (tof_measure(TOF_1_PIN_X) > 100)
                {
                    /// Rijden y-as met afstand Z
                    // ToF 4 + Z == ToF 4
                    int Z1Dist = Z1 + tof_measure(TOF_4_PIN_X);
                    while(tof_measure(TOF_4_PIN_X) < Z1Dist)
                    {
                        rijden(RIJRICHTING_Y_PLUS, UINT8_MAX);
                    }
                    rijden(RIJRICHTING_X_MIN, UINT8_MAX);
                    // ToF 4 < 30
                    if (tof_measure(TOF_4_PIN_X) < 50)
                    {
                        rijden(RIJRICHTING_Y_PLUS, UINT8_MAX);

                        // ToF 4 < 20
                        if (tof_measure(TOF_3_PIN_X) < 40)
                        {
                            // uit de functie baan wisselen
                            rijden(RIJRICHTING_X_MIN, UINT8_MAX);
                        }
                    }
                }
            }
        }
        // ToF 1 > 2
        else if(tof_measure(TOF_1_PIN_X) > tof_measure(TOF_2_PIN_X))
        {
            /// ToF 1 uitlezen
            // ToF 1 < 30
            if (tof_measure(TOF_1_PIN_X) < 40)
            {
                /// ToF 4 uitlezen (Y)
                uint16_t Y2 = tof_measure(TOF_4_PIN_X);
                /// afstand Z = Y-X
                uint16_t Z2 = Y2 - X;
                //  ToF 1 > 30
                if (tof_measure(TOF_1_PIN_X) > 100)
                {
                    /// Rijden y-as met afstand Z
                    // ToF 4 + Z == ToF 4
                    int Z2Dist = Z2 + tof_measure(TOF_4_PIN_X);
                    while(tof_measure(TOF_4_PIN_X) < Z2Dist)
                    {
                        rijden(RIJRICHTING_Y_PLUS, UINT8_MAX);
                    }
                    rijden(RIJRICHTING_X_PLUS, UINT8_MAX);
                    // ToF 4 < 30
                    if (tof_measure(TOF_4_PIN_X) < 50)
                    {
                        rijden(RIJRICHTING_Y_PLUS, UINT8_MAX);

                        // ToF 4 < 20
                        if (tof_measure(TOF_3_PIN_X) < 40)
                        {
                            // uit de functie baan wisselen
                            rijden(RIJRICHTING_X_PLUS, UINT8_MAX);
                        }
                    }
                }
            }
        }
    }
}

void agv_start_positie()
{
    agv_zet_vooruit();
    agv_zet_recht(RIJRICHTING_RECHTS);
    agv_muur_afstand(RIJRICHTING_ACHTERUIT, 10);
    agv_muur_afstand(RIJRICHTING_LINKS, 10);
}

void agv_start_navigatie()
{
    uint16_t rand_afstand = tof_measure(TOF_3_PIN_X);
    uint16_t target = 100;
    int snelheid = 80;
    int marge = 10;
    while (1)
    {
        uint16_t meting_rand = tof_measure(TOF_3_PIN_X);

        if (abs(meting_rand - rand_afstand) < marge)
        {
            uint16_t meting_target = tof_measure(TOF_1_PIN_X);

            if (abs(meting_target - target) < marge)
            {
                rijden_stop();
            }
            else if (meting_target > target)
            {
                rijden(RIJRICHTING_VOORUIT, snelheid);
            }
            else if (meting_target < target)
            {
                rijden(RIJRICHTING_ACHTERUIT, snelheid);
            }
        }
        else if (meting_rand > rand_afstand)
        {
            rijden(RIJRICHTING_RECHTS, snelheid);
        }
        else if (meting_rand < rand_afstand)
        {
            rijden(RIJRICHTING_LINKS, snelheid);
        }
    }
}
