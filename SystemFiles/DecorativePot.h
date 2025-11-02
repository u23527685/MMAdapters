/**
 * @file DecorativePot.h
 * @brief Concrete decorator for adding a decorative pot to a plant.
 */
 
#ifndef DECORATIVE_POT_H
#define DECORATIVE_POT_H

#include "PlantDecorator.h"

/**
 * @class DecorativePot
 * @brief Adds a decorative pot to the plant.
 */
class DecorativePot : public PlantDecorator {
public:
    /**
     * @brief Constructs a DecorativePot decorator.
     * @param plant Pointer to the plant being decorated.
     */
    DecorativePot(Plant* plant);

    /**
     * @brief Returns the description including the decorative pot detail.
     * @return A string describing the plant with a pot.
     */
    std::string getDescription() const override;

    /**
     * @brief Returns the total price including the decorative pot.
     * @return The updated price as a double.
     */
    double getPrice() const override;
};

#endif 
