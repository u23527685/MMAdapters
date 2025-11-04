#ifndef SHADESTRATEGY_H
#define SHADESTRATEGY_H

#include "Plant.h"
#include "SunlightStrategy.h"

class ShadeStrategy : public SunlightStrategy
{
  public:
    /**
     * @brief Applies the shade sunlight strategy to a plant.
     * This method applies the shade sunlight strategy to the given plant by
     * reducing its sunlight exposure.
     * @param p The plant to apply the shade sunlight strategy to.
     * @note The current implementation does not modify the plant's sunlight
     * level, as the setCurrentSunlight call adds 0 to the current value.
     */
    void applySunlight(Plant* p) override;
     /**
     * @brief Gets the name of the sunlight strategy
     * @details Returns the identifier for the shade strategy
     * @return std::string The name of the strategy ("Shade")
     */
    std::string getStrategyName() const override;
};

#endif