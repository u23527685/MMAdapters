/**
 * @file FullSunStrategy.h
 * @brief Concrete sunlight strategy applying full sunlight exposure to a plant.
 *
 * Implements the SunlightStrategy interface to provide maximum sunlight exposure
 * to a plant. Increases sunlight level by 60% per day, capped at the plant's
 * maximum allowed sunlight.
 *
 * @note Helps simulate sun-loving plants that thrive in full light.
 *
 * @warning Exceeding the maximum sunlight value resets it to the limit.
 *
 * @see SunlightStrategy
 * @see Plant
 *
 */
#ifndef FULLSUNSTRATEGY_H
#define FULLSUNSTRATEGY_H

#include "Plant.h"
#include "SunlightStrategy.h"

/**
 * @class FullSunStrategy
 * @brief Strategy for applying full sunlight to a Plant.
 *
 * Adjusts sunlight exposure to simulate plants requiring high sunlight levels.
 */
class FullSunStrategy : public SunlightStrategy{
public:
    /**
     * @brief Apply the full sun strategy to a Plant.
     * @param p Pointer to the Plant being exposed to sunlight.
     *
     * @note Increases sunlight exposure by 60% (hours/day).
     * @warning If exposure exceeds the max value, it is capped at the maximum.
     */
    void applySunlight(Plant* p) override;

    /**
     * @brief Get the name of this strategy.
     * @return "Full Sun Strategy".
     */
    std::string getStrategyName() const override;
};

#endif