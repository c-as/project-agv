#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "ldr.h"
#include "adc.h"
#include "motoren.h"
#include "BaanWisselen.h"
// Tof moet er nog bij

/// Hier zo'n typedef enum van maken
void get_afstandXYZ(int tof, Afstanden_XYZ welke)
{
    if (welke == AFSTAND_X)
    {
        switch (tof)
        {
        case 4:
            /// ToF 4 uitlezen; opslaan als int?
            break;
        }
    }

    else if (welke == AFSTAND_Y)
    {
        switch (tof)
        {
        case 4:
            /// ToF 4 uitlezen; opslaan als int?
            break;
        }
    }

    else if (welke == AFSTAND_Z)
    {
        /// AFSTAND_Y - AFSTAND_X
        switch (tof)
        {
        case 4:
            /// Afstand Y - X
            break;
        }
    }
}

void baan_wisselen()
{
    // ToF 1/2 < 170
    if (1)
    {
        /// ToF 1, 2 & 4 uitlezen (X)
        get_afstandXYZ(4, AFSTAND_X);
        rijden(RIJRICHTING_Y_PLUS, UINT8_MAX);
        // ToF 1 < 2
        if (1)
        {
            /// ToF 2 uitlezen
            // ToF 2 < 30
            if (1)
            {
                /// ToF 4 uitlezen (Y)
                get_afstandXYZ(4, AFSTAND_Y);
                /// afstand Z = Y-X
                get_afstandXYZ(4, AFSTAND_Z);
                // ToF 1 > 30
                if (1)
                {
                    /// Rijden y-as met afstand Z
                    // ToF 4 + Z == ToF 4
                    rijden(RIJRICHTING_X_MIN, UINT8_MAX);
                    // ToF 4 < 30
                    if (1)
                    {
                        rijden(RIJRICHTING_Y_PLUS, UINT8_MAX);

                        // ToF 4 < 20
                        if (1)
                        {
                            // uit de functie baan wisselen
                        }
                    }
                }
            }
        }
        // ToF 1 > 2
        else
        {
            /// ToF 1 uitlezen
            // ToF 1 < 30
            if (1)
            {
                /// ToF 4 uitlezen (Y)
                get_afstandXYZ(4, AFSTAND_Y);
                /// afstand Z = Y-X
                get_afstandXYZ(4, AFSTAND_Z);
                // ToF 1 > 30
                if (1)
                {
                    /// Rijden y-as met afstand Z
                    // ToF 4 + Z == ToF 4
                    rijden(RIJRICHTING_X_MIN, UINT8_MAX);
                    // ToF 4 < 30
                    if (1)
                    {
                        rijden(RIJRICHTING_Y_PLUS, UINT8_MAX);

                        // ToF 4 < 20
                        if (1)
                        {
                            // uit de functie baan wisselen
                        }
                    }
                }
            }
        }
    }
}
