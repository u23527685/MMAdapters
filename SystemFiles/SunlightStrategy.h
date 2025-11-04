/**
 * @file SunlightStrategy.h
 * @brief Abstract base class for sunlight strategies.
 *
 * Defines the interface for strategies that apply sunlight to plants.
 *
 */
#ifndef SUNLIGHTSTRATEGY_H
#define SUNLIGHTSTRATEGY_H

#include "Plant.h"

class SunlightStrategy{
protected:
    Plant* currentPlant; /**< Pointer to the plant currently exposed to sunlight. */
public:
    virtual ~SunlightStrategy() {}

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