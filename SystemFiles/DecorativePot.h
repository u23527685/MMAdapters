/**
 * @file DecorativePot.h
 * @brief Defines the DecorativePot class, a decorator that adds decorative pot
 * features to a plant.
 */

#ifndef DECORATIVE_POT_H
#define DECORATIVE_POT_H

#include "PlantDecorator.h"

/**
 * @class DecorativePot
 * @brief A concrete decorator that adds a decorative pot to a Plant object.
 */
class DecorativePot : public PlantDecorator
{
  public:
    /**
     * @brief Constructs a DecorativePot object that decorates a given Plant.
     * @param plant Pointer to the Plant object to be decorated.
     */
    DecorativePot(Plant *plant);

    /**
     * @brief Retrieves the description of the plant with the decorative pot.
     * @return A string describing the plant with the decorative pot.
     */
    std::string getDescription() const override;

    /**
     * @brief Calculates the total price of the plant including the decorative
     * pot.
     * @return The combined price of the plant and the decorative pot.
     */
    double getPrice() const override;
};

#endif
