#ifndef BAANWISSELEN_H_INCLUDED
#define BAANWISSELEN_H_INCLUDED

typedef enum
{
    AFSTAND_X,
    AFSTAND_Y,
    AFSTAND_Z,
} Afstanden_XYZ;

void get_afstandXYZ(int tof, Afstanden_XYZ);

#endif // BAANWISSELEN_H_INCLUDED
