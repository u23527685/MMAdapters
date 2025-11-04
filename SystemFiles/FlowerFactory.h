/**
 * @file FlowerFactory.h
 * @brief Factory for creating flower-type Plant objects.
 *
 * The FlowerFactory is a concrete implementation of PlantFactory
 * that constructs various flower-based Plant objects (e.g., Roses).
 *
 */
#ifndef FLOWERFACTORY_H
#define FLOWERFACTORY_H
#include "PlantFactory.h"
#include "Plant.h"
#include "Rose.h"

/**
 * @class FlowerFactory
 * @brief Concrete factory for creating flower-type Plants.
 *
 * Generates Plant instances based on flower types requested by clients.
 */
class FlowerFactory : public PlantFactory {
public:
    /**
     * @brief Create a flower plant of the specified type.
     * @param plantType The type of flower to create (e.g., "Rose").
     * @param price The initial price of the flower.
     * @return Pointer to a newly created Plant instance.
     */
    Plant* createPlant(std::string plantType, double price) override;
};

#endif
