/**
 * @file SpecialArrangement.h
 * @brief Concrete decorator for adding a special arrangement to a plant.
 */

#ifndef SPECIAL_ARRANGEMENT_H
#define SPECIAL_ARRANGEMENT_H

#include "PlantDecorator.h"

/**
 * @class SpecialArrangement
 * @brief Adds a special floral arrangement to a plant.
 */
class SpecialArrangement : public PlantDecorator {
public:
    /**
     * @brief Constructs a SpecialArrangement decorator.
     * @param plant Pointer to the plant being decorated.
     */
    SpecialArrangement(Plant* plant);

    /**
     * @brief Returns the description including the special arrangement.
     * @return A string describing the special arrangement.
     */
    std::string getDescription() const override;

    /**
     * @brief Returns the total price including the special arrangement.
     * @return The updated price as a double.
     */
    double getPrice() const override;
};

#endif 
