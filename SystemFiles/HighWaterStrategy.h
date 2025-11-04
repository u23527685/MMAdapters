/**
 * @file HighWaterStrategy.h
 * @brief Concrete watering strategy that applies high water levels to a plant.
 *
 * HighWaterStrategy implements the WaterStrategy interface and provides
 * plants with a large amount of water during watering operations.
 *
 * @see WaterStrategy
 * @see Plant
 *
 */
#ifndef HIGHWATERSTRATEGY_H
#define HIGHWATERSTRATEGY_H

#include "Plant.h"
#include "WateringStrategy.h"

/**
 * @class HighWaterStrategy
 * @brief Strategy for applying a high amount of water to a plant.
 */
class HighWaterStrategy: public WaterStrategy{
public:
     /**
     * @brief Applies the high water strategy to a plant.
     *
     * Increases the plant's water level by 100ml, capped at the plant’s
     * maximum water capacity.
     *
     * @param p Pointer to the plant receiving water.
     */
    void applyWater(Plant* p) override;

    /**
     * @brief Gets the name of this watering strategy.
     * @return String representing the strategy name.
     */
    std::string getStrategyName() const override;
};

#endif