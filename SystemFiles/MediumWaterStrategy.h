#ifndef MEDIUMWATERSTRATEGY_H
#define MEDIUMWATERSTRATEGY_H

#include "Plant.h"
#include "WateringStrategy.h"

class MediumWaterStrategy: public WaterStrategy{
public:
    /**
 * @brief Applies the medium water strategy to a plant.
 * This method applies the medium water strategy to the given plant by increasing its water level.
 * @param p The plant to apply the medium water strategy to.
 * @note The water level is increased by 50ml.
 * @note The plant's water level will be capped at its maximum water level if the increase exceeds the remaining capacity.
 */
    void applyWater(Plant* p) override;
    std::string getStrategyName() const override;
};

#endif