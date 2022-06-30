#include <avr/io.h>


#define led_aan_rood        PORTG |= (1 << PG0)
#define led_aan_blauw       PORTG |= (1 << PG2)
#define led_uit_rood        PORTG &= ~(1 << PG0)
#define led_uit_blauw       PORTG &= ~(1 << PG2)

void led_init()
{
    DDRG &= ~(1 << PG0);
    DDRG &= ~(1 << PG2);
}


void led_check(int stand)
{
    if(stand)
    {
        led_aan_blauw;
        led_aan_rood;
    }
    else if(stand == 0)
    {
        led_uit_blauw;
        led_uit_rood;
    }
}

