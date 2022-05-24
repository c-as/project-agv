/*
 * h_bridge.c - XvR 2020
 *
 * Use 8-bit timer. Uses interrupts in order to be able
 * to use the pins on the multifunction shield
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "h_bridge.h"

extern int motorselector;

ISR(TIMER0_OVF_vect)
{
	if (OCR0A == 0 && OCR0B == 0)
	{
		if(motorselector == 1)
		{
		PORT_RPWM1 &= ~(1<<PIN_RPWM1);
		PORT_LPWM1 &= ~(1<<PIN_LPWM1);
		}
		if(motorselector == 2)
		{
		PORT_RPWM2 &= ~(1<<PIN_RPWM2);
		PORT_LPWM2 &= ~(1<<PIN_LPWM2);
		}
		if(motorselector == 3)
		{
		PORT_RPWM3 &= ~(1<<PIN_RPWM3);
		PORT_LPWM3 &= ~(1<<PIN_LPWM3);
		}
		if(motorselector == 4)
		{
		PORT_RPWM4 &= ~(1<<PIN_RPWM4);
		PORT_LPWM4 &= ~(1<<PIN_LPWM4);
		}
	}
	else if (OCR0A != 0)
	{
		if(motorselector == 1)
		{
		PORT_LPWM1 &= ~(1<<PIN_LPWM1);
		PORT_RPWM1 |= (1<<PIN_RPWM1);
		}
		if(motorselector == 2)
		{
		PORT_LPWM2 &= ~(1<<PIN_LPWM2);
		PORT_RPWM2 |= (1<<PIN_RPWM2);
		}
		if(motorselector == 3)
		{
		PORT_LPWM3 &= ~(1<<PIN_LPWM3);
		PORT_RPWM3 |= (1<<PIN_RPWM3);
		}
		if(motorselector == 4)
		{
		PORT_LPWM4 &= ~(1<<PIN_LPWM4);
		PORT_RPWM4 |= (1<<PIN_RPWM4);
		}
	}
	else if (OCR0B != 0)
	{
		if(motorselector == 1)
		{
		PORT_RPWM1 &= ~(1<<PIN_RPWM1);
		PORT_LPWM1 |= (1<<PIN_LPWM1);
		}
		if(motorselector == 2)
		{
		PORT_RPWM2 &= ~(1<<PIN_RPWM2);
		PORT_LPWM2 |= (1<<PIN_LPWM2);
		}
		if(motorselector == 3)
		{
		PORT_RPWM3 &= ~(1<<PIN_RPWM3);
		PORT_LPWM3 |= (1<<PIN_LPWM3);
		}
		if(motorselector == 4)
		{
		PORT_RPWM4 &= ~(1<<PIN_RPWM4);
		PORT_LPWM4 |= (1<<PIN_LPWM4);
		}
	}
}

ISR(TIMER0_COMPA_vect)
{
	if (OCR0A != 255)
	{
		if(motorselector == 1)
		{
		PORT_RPWM1 &= ~(1<<PIN_RPWM1);
		}
		if(motorselector == 2)
		{
		PORT_RPWM2 &= ~(1<<PIN_RPWM2);
		}
		if(motorselector == 3)
		{
		PORT_RPWM3 &= ~(1<<PIN_RPWM3);
		}
		if(motorselector == 4)
		{
		PORT_RPWM4 &= ~(1<<PIN_RPWM4);
		}
	}
}

ISR(TIMER0_COMPB_vect)
{
	if (OCR0B != 255)
	{
		if(motorselector == 1)
		{
		PORT_LPWM1 &= ~(1<<PIN_LPWM1);
		}
		if(motorselector == 2)
		{
		PORT_LPWM2 &= ~(1<<PIN_LPWM2);
		}
		if(motorselector == 3)
		{
		PORT_LPWM3 &= ~(1<<PIN_LPWM3);
		}
		if(motorselector == 4)
		{
		PORT_LPWM4 &= ~(1<<PIN_LPWM4);
		}
	}
}

void init_h_bridge(void)
{
	// Config pins as output
	DDR_RPWM1 |= (1<<PIN_RPWM1);
	DDR_LPWM1 |= (1<<PIN_LPWM1);

	// Output low
	PORT_RPWM1 &= ~(1<<PIN_RPWM1);
	PORT_LPWM1 &= ~(1<<PIN_LPWM1);

	// Use mode 0, clkdiv = 64
	TCCR0A = 0;
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00);

	// Disable PWM output
	OCR0A = 0;
	OCR0B = 0;

	// Interrupts on OCA, OCB and OVF
	TIMSK0 = (1<<OCIE0B) | (1<<OCIE0A) | (1<<TOIE0);

	sei();
}

void h_bridge_set_percentage(signed char percentage)
{
	if (percentage >= -100 && percentage <= 100)
	{
		if (percentage >= 0)
		{
			// Disable LPWM, calculate RPWM
			OCR0B = 0;
			OCR0A = (255*percentage)/100;
		}
		else // percentage < 0
		{
			// Disable RPWM, calculate LPWM
			OCR0A = 0;
			OCR0B = (255*percentage)/-100;
		}
	}
}
