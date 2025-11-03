#ifndef TREEFACTORY_H
#define TREEFACTORY_H
#include "PlantFactory.h"
#include "Plant.h"
#include "Oak.h"

/**
 * @class TreeFactory
 * @brief Concrete factory for creating tree plants
 * 
 * This class implements the PlantFactory interface to create
 * specific tree-type plants like Oak trees.
 */
class TreeFactory : public PlantFactory {
public:
    /**
     * @brief Creates a tree plant of the specified type
     * @param plantType The type of tree to create (e.g., "Oak")
     * @param price The price of the tree plant
     * @return Pointer to the newly created Plant object
     */
    Plant* createPlant(std::string plantType, double price) override;
};

#endif
