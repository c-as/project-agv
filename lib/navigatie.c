#include <stdlib.h>
#include <avr/io.h>
#include "tof/tof.h"
#include "motoren.h"

#define VOORUIT_DIFF 50
// zet agv parallel
void agv_zet_recht()
{
    agv_zet_vooruit();

    uint16_t meting = tof_measure(TOF_VOOR);

    // draai super sloom
    rijden(RIJRICHTING_CW, 10);

    int last_diff = 0;

    // als het goed is wordt het verschil nu alleen maar kleiner totdat de agv recht staat
    while (1)
    {
        int diff = meting - tof_measure(TOF_VOOR);

        if (diff > last_diff)
        {
            return;
        }

        last_diff = diff;
    }

    rijden_stop();
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

        if (diff_rechts > VOORUIT_DIFF && diff_links > VOORUIT_DIFF)
        {
            break;
        }
    }

    rijden_stop();
}