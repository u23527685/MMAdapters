#ifndef MEDIUMWATERSTRATEGY_H
#define MEDIUMWATERSTRATEGY_H

#include "Plant.h"
#include "WateringStrategy.h"

class MediumWaterStrategy: public WaterStrategy{
public:
    void applyWater(Plant* p) override;
};

#endif