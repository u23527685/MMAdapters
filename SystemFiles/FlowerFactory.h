/**
 * @file FlowerFactory.h
 * @brief Header file for the FlowerFactory class
 */

#ifndef FLOWERFACTORY_H
#define FLOWERFACTORY_H

#include "PlantFactory.h"
#include "Plant.h"
#include "Rose.h"

/**
 * @class FlowerFactory
 * @brief Factory class for creating flower type plants
 * @details Implements the factory method pattern to create different types of flowers
 */
class FlowerFactory : public PlantFactory {
public:
    /**
     * @brief Creates a new flower plant object
     * @param plantType The type of flower to create
     * @param price The price of the flower
     * @return Plant* Pointer to the newly created Plant object
     */
    Plant* createPlant(std::string plantType, double price) override;
};

#endif