/*
 */

#include <avr/io.h>
#include "rand-volgen.h"
#include "tof/tof.h"
#include <stdlib.h>
#include "motoren.h"

// afstanden in mm
#define RAND_AFSTAND 50
#define MIN_DIFF 5

void RandVolgen()
{
    while (1)
    {
        int meting = 0; // tof_measure();
        if (abs(RAND_AFSTAND - meting) > MIN_DIFF)
        {
            if (RAND_AFSTAND > meting)
            {
                rijden(RIJRICHTING_LINKS, UINT8_MAX);
            }
            else
            {
                rijden(RIJRICHTING_RECHTS, UINT8_MAX);
            }
        }
        else
        {
            rijden(RIJRICHTING_VOORUIT, UINT8_MAX);
        }
    }
}
