/*
 * h_bridge.h - XvR 2020
 */

#ifndef _H_BRIDGE_H_
#define _H_BRIDGE_H_

// These pins are available on the shield via the header:
//
//		Mega	Uno
// digital 5	PE3	PD5
// digital 6	PH3	PD6
// digital 9	PH6	PB1
// analog 5	PF5	PC5

// The settings below are for the Mega, modify
// in case you want to use other pins
//=======================================
//motor 1
//=======================================
#define PORT_RPWM1	PORTH
#define PIN_RPWM1	PH6
#define DDR_RPWM1	DDRH

#define PORT_LPWM1	PORTF
#define PIN_LPWM1	PF5
#define DDR_LPWM1	DDRF

//=======================================
//motor 2
//=======================================
#define PORT_RPWM2	PORTH
#define PIN_RPWM2	PH6
#define DDR_RPWM2	DDRH

#define PORT_LPWM2	PORTF
#define PIN_LPWM2	PF5
#define DDR_LPWM2	DDRF

//=======================================
//motor 3
//=======================================
#define PORT_RPWM3	PORTH
#define PIN_RPWM3	PH6
#define DDR_RPWM3	DDRH

#define PORT_LPWM3	PORTF
#define PIN_LPWM3	PF5
#define DDR_LPWM3	DDRF

//=======================================
//motor 4
//=======================================
#define PORT_RPWM4	PORTH
#define PIN_RPWM4	PH6
#define DDR_RPWM4	DDRH

#define PORT_LPWM4	PORTF
#define PIN_LPWM4	PF5
#define DDR_LPWM4	DDRF


void init_h_bridge(void);
void h_bridge_set_percentage(signed char percentage);

#endif /* _H_BRIDGE_H_ */
