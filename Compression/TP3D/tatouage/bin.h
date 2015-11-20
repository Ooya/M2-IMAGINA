#include "face.h"
#include "point.h"
#include "maillage.h"

#ifndef BIN_H
#define BIN_H

class Bin
{
public:
    float rMin, rMax;
    Bin();
    Bin(float rMin, float rMax);
    void normalise();
    void normaliseInv();
};

#endif // BIN_H
