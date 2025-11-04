/**
 * @file PartialSunStrategy.h
 * @brief Concrete sunlight strategy providing moderate sunlight exposure.
 *
 * PartialSunStrategy increases a plant’s sunlight exposure moderately,
 * suitable for plants that thrive in partial sun conditions.
 *
 * @see SunlightStrategy
 * @see Plant
 *
 * @author
 * Jay Lopes
 */
#ifndef PARTIALSUNSTRATEGY_H
#define PARTIALSUNSTRATEGY_H

#include "Plant.h"
#include "SunlightStrategy.h"

/**
 * @class PartialSunStrategy
 * @brief Strategy for applying partial sunlight to a plant.
 */
class PartialSunStrategy : public SunlightStrategy{
public:
    /**
     * @brief Applies the partial sun strategy to a plant.
     *
     * Increases sunlight by 40% of the plant’s maximum capacity.
     * Caps at the maximum sunlight threshold.
     *
     * @param p Pointer to the plant receiving sunlight.
     */
    void applySunlight(Plant* p) override;

    /**
     * @brief Retrieves the strategy name.
     * @return String representing the strategy type.
     */
    std::string getStrategyName() const override;
};

#endif