/**
* @class SunlightStrategy
 * @brief Abstract base class for sunlight strategies.
 * This class defines the interface for sunlight strategies, which determine how much sunlight to apply to a plant.
 * Concrete strategy classes should inherit from this class and implement the applySunlight and getStrategyName methods.
 */


#ifndef SUNLIGHTSTRATEGY_H
#define SUNLIGHTSTRATEGY_H

#include "Plant.h"

class SunlightStrategy{
protected:
    /**
    * @var currentPlant
    * @brief The current plant being put/or not being put in the sun.
    */
    Plant* currentPlant;
public:
    /**
     * @brief Applies sun to a plant according to the strategy.
     * This method must be implemented by concrete strategy classes.
     * @param p The plant to be put in the sun.
     */
    virtual void applySunlight(Plant* p) =0;
    /**
    * @brief Gets the name of the sunlight strategy.
    * This method must be implemented by concrete strategy classes.
    * @return The name of the sun strategy.
    */
    virtual std::string getStrategyName() const = 0;
};

#endif