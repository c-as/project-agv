
#ifndef _motorenDefines_H_
#define _motorenDefines_H_

typedef enum
{
    RIJRICHTING_VOORUIT,
    RIJRICHTING_ACHTERUIT,
    RIJRICHTING_CW,
    RIJRICHTING_CCW,
} RijRichting;

typedef enum
{
    MOTORRICHTING_CW,
    MOTORRICHTING_CCW,
} MotorRichting;

void init_motoren(void);
void motor(int motor, MotorRichting kant);
void RijdenX_as(RijRichting kant);
void RijdenY_as(RijRichting kant);
void Draaien(RijRichting kant);
void motoren_test();

#endif
