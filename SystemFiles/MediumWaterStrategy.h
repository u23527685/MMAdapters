/**
 * @file MediumWaterStrategy.h
 * @brief Defines the MediumWaterStrategy for moderate watering needs.
 *
 * This strategy provides a balanced water increase suitable for most plants.
 *
 * @author 
 * Jay Lopes
 */
#ifndef MEDIUMWATERSTRATEGY_H
#define MEDIUMWATERSTRATEGY_H

#include "Plant.h"
#include "WateringStrategy.h"

/**
 * @class MediumWaterStrategy
 * @brief Strategy for moderately watering plants.
 *
 * Applies a 50ml water increase and prevents overflow beyond maximum capacity.
 */
class MediumWaterStrategy: public WaterStrategy{
public:
    /**
     * @brief Applies the medium water strategy to the plant.
     * @param p The plant to water.
     * @note Increases the plant’s water level by 50ml.
     * @warning Caps the water level at the maximum allowed value.
     */
    void applyWater(Plant* p) override;

    /**
     * @brief Gets the name of this watering strategy.
     * @return A string with the strategy’s name.
     */
    std::string getStrategyName() const override;
};

#endif