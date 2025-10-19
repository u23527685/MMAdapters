#ifndef HIGHWATERSTRATEGY_H
#define HIGHWATERSTRATEGY_H

#include "Plant.h"
#include "WateringStrategy.h"

class HighWaterStrategy: public WaterStrategy{
public:
    void applyWater(Plant* p) override;
};

#endif