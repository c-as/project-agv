/*
 */

#include <avr/io.h>
#include "rand-volgen.h"
#include "tof/tof.h"
#include <math.h>
#include "motoren.h"

// afstanden in mm
#define RAND_AFSTAND 50
#define MIN_DIFF 5

void RandVolgen()
{
    while (1)
    {
        int meting = tof_measure();
        if (abs(RAND_AFSTAND - meting) > MIN_DIFF)
        {
            if (RAND_AFSTAND > meting)
            {
                RijdenY_as(RIJRICHTING_VOORUIT);
            }
            else
            {
                RijdenY_as(RIJRICHTING_ACHTERUIT);
            }
        }
        else
        {
            RijdenX_as(RIJRICHTING_VOORUIT);
        }
    }
}
