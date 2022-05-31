
#ifndef _motorenDefines_H_
#define _motorenDefines_H_

//=======================================
// motor 1
//=======================================
#define PORT_RPWM1 PORTE
#define PIN_RPWM1 PE4
#define DDR_RPWM1 DDRE

#define PORT_LPWM1 PORTE
#define PIN_LPWM1 PE5
#define DDR_LPWM1 DDRE

//=======================================
// motor 2
//=======================================
#define PORT_RPWM2 PORTG
#define PIN_RPWM2 PG5
#define DDR_RPWM2 DDRG

#define PORT_LPWM2 PORTE
#define PIN_LPWM2 PE3
#define DDR_LPWM2 DDRE

//=======================================
// motor 3
//=======================================
#define PORT_RPWM3 PORTH
#define PIN_RPWM3 PH3
#define DDR_RPWM3 DDRH

#define PORT_LPWM3 PORTH
#define PIN_LPWM3 PH4
#define DDR_LPWM3 DDRH

//=======================================
// motor 4
//=======================================
#define PORT_RPWM4 PORTH
#define PIN_RPWM4 PH5
#define DDR_RPWM4 DDRH

#define PORT_LPWM4 PORTH
#define PIN_LPWM4 PH6
#define DDR_LPWM4 DDRH

void init_motoren(void);
void motor(int motor, int kant);
void RijdenX_as(int kant);
void RijdenY_as(int kant);
void Draaien(int kant);

#endif /* _motorenDefines_H_ */
