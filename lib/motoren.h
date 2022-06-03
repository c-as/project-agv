
#ifndef _motorenDefines_H_
#define _motorenDefines_H_

typedef enum
{
    RIJRICHTING_VOORUIT,
    RIJRICHTING_X_PLUS,
    RIJRICHTING_ACHTERUIT,
    RIJRICHTING_X_MIN,
    RIJRICHTING_LINKS,
    RIJRICHTING_Y_PLUS,
    RIJRICHTING_RECHTS,
    RIJRICHTING_Y_MIN,
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
void rijden(RijRichting kant);
void motoren_test();

#endif
