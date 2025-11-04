/**
 * @file FertilizerStrategy.h
 * @brief Defines the abstract interface for plant fertilizer strategies.
 *
 * This interface allows for different fertilizer strategies to be applied
 * polymorphically to various plant types.
 *
 */
#ifndef FERTILIZERSTRATEGY_H
#define FERTILIZERSTRATEGY_H

#include "Plant.h"

/**
 * @class FertilizerStrategy
 * @brief Abstract base for fertilizer behavior strategies.
 */
class FertilizerStrategy{
protected:
    Plant* currentPlant; /**< Pointer to the plant being fertilized. */
public:
    virtual ~FertilizerStrategy() {}
    /**
     * @brief Applies the fertilizer strategy to a plant.
     * This is a pure virtual function that must be implemented by concrete subclasses.
     * @param p The plant to apply the fertilizer strategy to.
     */
    virtual void applyFertilizer(Plant* p)=0;
    
    /**
    * @brief Gets the name of the fertilizer strategy.
    * This is a pure virtual function that must be implemented by concrete subclasses.
    * @return The name of the fertilizer strategy.
    */
    virtual std::string getStrategyName() const = 0;
};

#endif