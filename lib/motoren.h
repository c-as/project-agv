
#ifndef _motorenDefines_H_
#define _motorenDefines_H_

#define RIJRICHTING_X_PLUS RIJRICHTING_VOORUIT
#define RIJRICHTING_X_MIN RIJRICHTING_ACHTERUIT
#define RIJRICHTING_Y_PLUS RIJRICHTING_LINKS
#define RIJRICHTING_Y_MIN RIJRICHTING_RECHTS

#define RIJRICHTING_TOF_1 RIJRICHTING_VOORUIT
#define RIJRICHTING_TOF_2 RIJRICHTING_ACHTERUIT
#define RIJRICHTING_TOF_3 RIJRICHTING_RECHTS
#define RIJRICHTING_TOF_4 RIJRICHTING_LINKS

typedef enum
{
    RIJRICHTING_VOORUIT,
    RIJRICHTING_ACHTERUIT,
    RIJRICHTING_LINKS,
    RIJRICHTING_RECHTS,
    RIJRICHTING_CW,
    RIJRICHTING_CCW,
} RijRichting;

typedef enum
{
    MOTORRICHTING_CW,
    MOTORRICHTING_CCW,
} MotorRichting;

void init_motoren();
void motor_zet_richting(int motor, MotorRichting kant);
void motor_zet_duty(uint8_t duty);
void rijden(RijRichting kant, uint8_t duty);
void rijden_stop();
void motoren_test();

#endif
