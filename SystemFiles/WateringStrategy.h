#ifndef WATERSTRATEGY_H
#define WATERSTRATEGY_H

#include "Plant.h"

class WaterStrategy{
protected:
    Plant* currentPlant;
public:
    virtual void applyWater(Plant* p) = 0;
};

#endif