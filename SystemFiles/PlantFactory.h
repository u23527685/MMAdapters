/**
 * @file PlantFactory.h
 * @brief Abstract factory interface for creating Plant objects.
 *
 * The PlantFactory defines a consistent interface for creating different
 * types of plant objects. Concrete subclasses (e.g., FlowerFactory) must
 * implement the creation logic.
 *
 * @see FlowerFactory
 * @see Plant
 *
 * @author
 * Mthokozisi Duba
 */
#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H
#include "Plant.h"

/**
 * @class PlantFactory
 * @brief Abstract base class for plant creation factories.
 */
class PlantFactory {
public:
    /**
     * @brief Pure virtual method to create a plant
     * @param plantType The type of plant to create
     * @param price The price of the plant
     * @return Pointer to the newly created Plant object
     */
    virtual Plant* createPlant(std::string plantType, double price) = 0;
    
    virtual ~PlantFactory() {}
};

#endif
