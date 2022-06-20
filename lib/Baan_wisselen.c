#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "ldr.h"
#include "adc.h"
#include "motoren.h"
#include "BaanWisselen.h"
#include "tof/tof.h"

void baan_wisselen()
{
    // ToF 1/2 < 170
    if (1)
    {
        /// ToF 1, 2 & 4 uitlezen (X)
        tof_measure(TOF_1_PIN_X);
        tof_measure(TOF_2_PIN_X);
        uint16_t X = tof_measure(TOF_4_PIN_X);
        rijden(RIJRICHTING_Y_PLUS, UINT8_MAX);
        // ToF 1 < 2
        if (tof_measure(TOF_1_PIN_X) < tof_measure(TOF_2_PIN_X))
        {
            /// ToF 2 uitlezen
            tof_measure(TOF_2_PIN_X);
            // ToF 2 < 30
            if (tof_measure(TOF_2_PIN_X) < 30)
            {
                /// ToF 4 uitlezen (Y)
                uint16_t Y1 = tof_measure(TOF_4_PIN_X);
                /// afstand Z = Y-X
                uint16_t Z1 = Y1 - X;
                // ToF 1 > 30
                if (tof_measure(TOF_1_PIN_X))
                {
                    /// Rijden y-as met afstand Z
                    // ToF 4 + Z == ToF 4
                    rijden(RIJRICHTING_X_MIN, UINT8_MAX);
                    // ToF 4 < 30
                    if (tof_measure(TOF_4_PIN_X) < 30)
                    {
                        rijden(RIJRICHTING_Y_PLUS, UINT8_MAX);

                        // ToF 4 < 20
                        if (tof_measure(TOF_4_PIN_X) < 20)
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
            if (tof_measure(TOF_1_PIN_X) < 30)
            {
                /// ToF 4 uitlezen (Y)
                uint16_t Y2 = tof_measure(TOF_4_PIN_X);
                /// afstand Z = Y-X
                uint16_t Z2 = Y2 - X;
                // ToF 1 > 30
                if(tof_measure(TOF_1_PIN_X) > 30)
                {
                    /// Rijden y-as met afstand Z
                    // ToF 4 + Z == ToF 4
                    rijden(RIJRICHTING_X_MIN, UINT8_MAX);
                    // ToF 4 < 30
                    if (tof_measure(TOF_4_PIN_X) < 30)
                    {
                        rijden(RIJRICHTING_Y_PLUS, UINT8_MAX);

                        // ToF 4 < 20
                        if (tof_measure(TOF_4_PIN_X) < 20)
                        {
                            // uit de functie baan wisselen
                        }
                    }
                }
            }
        }
    }
}
