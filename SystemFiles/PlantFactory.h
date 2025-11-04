#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H
#include "Plant.h"

/**
 * @class PlantFactory
 * @brief Abstract base class for plant creation factories
 *
 * This class defines the interface for factory classes that create
 * different types of plants. Concrete factories should inherit from
 * this class and implement the createPlant method.
 */
class PlantFactory
{
  public:
    /**
     * @brief Pure virtual method to create a plant
     * @param plantType The type of plant to create
     * @param price The price of the plant
     * @return Pointer to the newly created Plant object
     */
    virtual Plant *createPlant(std::string plantType, double price) = 0;

    virtual ~PlantFactory() {}
};

#endif
