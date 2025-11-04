/**
 * @file DecorativePot.h
 * @brief Decorator class adding a decorative pot feature to a Plant.
 *
 * DecorativePot is a concrete decorator extending PlantDecorator. It enhances
 * the description and price of a plant by adding a decorative pot.
 *
 * @author
 * Jerusha Thaver
 */
#ifndef DECORATIVE_POT_H
#define DECORATIVE_POT_H

#include "PlantDecorator.h"

/**
 * @class DecorativePot
 * @brief Concrete decorator that adds a decorative pot to a Plant.
 *
 * Enhances the plant's visual appeal and increases its price.
 */
class DecorativePot : public PlantDecorator {
public:
    /**
     * @brief Construct a DecorativePot decorator for the given Plant.
     * @param plant Non-owning pointer to the Plant being decorated.
     */
    DecorativePot(Plant* plant);

    /**
     * @brief Get the description including decorative pot details.
     * @return Augmented description string.
     */
    std::string getDescription() const override;

    /**
     * @brief Get the total price including the decorative pot.
     * @return Combined price as a double.
     */
    double getPrice() const override;
};

#endif 
