#ifndef PARTIALSUNSTRATEGY_H
#define PARTIALSUNSTRATEGY_H

#include "Plant.h"
#include "SunlightStrategy.h"

class PartialSunStrategy : public SunlightStrategy{
public:
    /**
 * @brief Applies the partial sun strategy to a plant.
 * This method applies the partial sun strategy to the given plant by increasing its sunlight exposure.
 * @param p The plant to apply the partial sun strategy to.
 * @note The sunlight level is increased by 40% (hrs/day).
 * @note The plant's sun level will be capped at its maximum water level if the increase exceeds the remaining capacity.
 */
    void applySunlight(Plant* p) override;
    std::string getStrategyName() const override;
};

#endif