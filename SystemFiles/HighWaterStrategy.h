#ifndef HIGHWATERSTRATEGY_H
#define HIGHWATERSTRATEGY_H

#include "Plant.h"
#include "WateringStrategy.h"

class HighWaterStrategy : public WaterStrategy
{
  public:
    /**
     * @brief Applies the high water strategy to a plant.
     * This method applies the high water strategy to the given plant by
     * increasing its water level with a large amount.
     * @param p The plant to apply the high water strategy to.
     * @note The water level is increased by 100ml.
     * @note The plant's water level will be capped at its maximum water level
     * if the increase exceeds the remaining capacity.
     */
    void applyWater(Plant *p) override;
    std::string getStrategyName() const override;
};

#endif