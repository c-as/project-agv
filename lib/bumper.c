#include "pinio.h"
#include "motoren.h"
#include "bumper.h"
#include "time.h"

#define BUMPER_VRIJ_WACHTTIJD_MS 2000
#define BUMPER_PIN MEGA_PIN_D52_DIGITAL

void bumper_init()
{
    // bumper werkt als simpel knopje
    pin_set_mode(BUMPER_PIN, PINMODE_DIGITAL_INPUT_PULLUP); // gebruik interne pullup weerstand
}

void bumper_check()
{
    // sla op wat de agv aan het doen was
    volatile int vorige_rijrichting = current_rijrichting;
    volatile int vorige_duty = current_duty;

    if (pin_get_input(BUMPER_PIN))
    {
        while (pin_get_input(BUMPER_PIN))
        {
            rijden_stop();
        }

        // wacht even voordat we weer gaan rijden
        wacht_millis(BUMPER_VRIJ_WACHTTIJD_MS);

        rijden(vorige_rijrichting, vorige_duty);
    }
}