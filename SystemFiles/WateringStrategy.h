/**
* @class WaterStrategy
 * @brief Abstract base class for water strategies.
 * This class defines the interface for water strategies, which determine how much water to apply to a plant.
 * Concrete strategy classes should inherit from this class and implement the applyWater and getStrategyName methods.
 */

#ifndef WATERSTRATEGY_H
#define WATERSTRATEGY_H

#include "Plant.h"

/**
 * @class WaterStrategy
 * @brief Abstract base class for defining water strategies.
 *
 * This class defines the interface for all watering strategies, determining
 * how much and how often a plant should be watered.
 */
class WaterStrategy{
protected:
    /**
     * @var currentPlant
     * @brief The current plant being watered.
     */
    Plant* currentPlant;
public:
    virtual ~WaterStrategy() {}
    /**
     * @brief Applies water to a plant according to the strategy.
     * This method must be implemented by concrete strategy classes.
     * @param p The plant to water.
     */
    virtual void applyWater(Plant* p) = 0;
    /**
    * @brief Gets the name of the water strategy.
    * This method must be implemented by concrete strategy classes.
    * @return The name of the water strategy.
    */
    virtual std::string getStrategyName() const = 0;
};

#endif