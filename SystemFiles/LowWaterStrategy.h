#ifndef LOWWATERSTRATEGY_H
#define LOWWATERSTRATEGY_H

#include "Plant.h"
#include "WateringStrategy.h"

class LowWaterStrategy: public WaterStrategy{
public:
    /**
 * @brief Overview of the applyWater method.
 * This method applies the low water strategy to the given plant by increasing its water level with a small amount.
 * @param p The plant to apply the low water strategy to.
 * @note The water level is increased by 20ml.
 *@note The plant's water level will be capped at its maximum water level if the increase exceeds the remaining capacity.
 */
    void applyWater(Plant* p) override;
    std::string getStrategyName() const override;
};

#endif