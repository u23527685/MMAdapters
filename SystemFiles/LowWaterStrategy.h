#ifndef LOWWATERSTRATEGY_H
#define LOWWATERSTRATEGY_H

#include "Plant.h"
#include "WateringStrategy.h"

class LowWaterStrategy: public WaterStrategy{
public:
    void applyWater(Plant* p) override;
};

#endif