/**
 * @file LowWaterStrategy.h
 * @brief Defines the LowWaterStrategy class used for minimal watering.
 *
 * This strategy increases a plant’s water level by a small, controlled amount,
 * ensuring it doesn’t exceed its maximum capacity.
 *
 * @author 
 * Jay Lopes
 */
#ifndef LOWWATERSTRATEGY_H
#define LOWWATERSTRATEGY_H

#include "Plant.h"
#include "WateringStrategy.h"

/**
 * @class LowWaterStrategy
 * @brief Strategy for plants requiring minimal water intake.
 *
 * Applies a 20ml water increase, capping the level at the plant’s maximum water limit.
 */
class LowWaterStrategy: public WaterStrategy{
public:
    /**
     * @brief Applies the low water strategy to a plant.
     * @param p The target plant.
     * @note Increases water level by 20ml.
     * @warning Caps the value at the plant’s maximum water level.
     */
    void applyWater(Plant* p) override;

    /**
     * @brief Retrieves the name of this watering strategy.
     * @return A string representing the strategy name.
     */
    std::string getStrategyName() const override;
};

#endif