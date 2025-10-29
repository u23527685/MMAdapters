#ifndef FULLSUNSTRATEGY_H
#define FULLSUNSTRATEGY_H

#include "Plant.h"
#include "SunlightStrategy.h"

class FullSunStrategy : public SunlightStrategy{
public:
    /**
 * @brief Applies the full sun strategy to a plant.
 *
 * This method applies the full sun strategy to the given plant by increasing its sunlight exposure.
 *
 * @param p The plant to apply the full sun strategy to.
 *
 * @note The sunlight level is increased by 60% (hrs/day).
 * @warning If sunlight exceeds max sunlight its set to the max sunlight amount
 */
    void applySunlight(Plant* p) override;
    std::string getStrategyName() const override;
};

#endif