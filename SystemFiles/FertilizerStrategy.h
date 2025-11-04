#ifndef FERTILIZERSTRATEGY_H
#define FERTILIZERSTRATEGY_H

#include "Plant.h"

/**
 * @class FertilizerStrategy
 * @brief Abstract base class for fertilizer strategies.
 * This class provides an interface for different fertilizer strategies to be
 * applied to plants.
 */
class FertilizerStrategy
{
  protected:
    /**
     * @brief The current plant being fertilized.
     */
    Plant *currentPlant;

  public:
    virtual ~FertilizerStrategy() {}
    /**
     * @brief Applies the fertilizer strategy to a plant.
     * This is a pure virtual function that must be implemented by concrete
     * subclasses.
     * @param p The plant to apply the fertilizer strategy to.
     */
    virtual void applyFertilizer(Plant *p) = 0;
    /**
     * @brief Gets the name of the fertilizer strategy.
     * This is a pure virtual function that must be implemented by concrete
     * subclasses.
     * @return The name of the fertilizer strategy.
     */
    virtual std::string getStrategyName() const = 0;
};

#endif