/**
 * @file SpecialArrangement.h
 * @brief Header file for the SpecialArrangement decorator class
 * @authors Jerusha, Rachel
 * @date October 27, 2025
 */

#ifndef SPECIAL_ARRANGEMENT_H
#define SPECIAL_ARRANGEMENT_H

#include "PlantDecorator.h"

/**
 * @class SpecialArrangement
 * @brief Decorator class for adding special arrangement features to plants
 * @details Provides functionality to enhance a plant with special arrangement decorations
 *          and adjusts the price accordingly
 * @authors Jerusha, Rachel
 */
class SpecialArrangement : public PlantDecorator {
public:
    /**
     * @brief Constructor for SpecialArrangement decorator
     * @param plant Pointer to the Plant object being decorated
     * @return None (constructor)
     * @authors Jerusha, Rachel
     */
    SpecialArrangement(Plant* plant);

    /**
     * @brief Gets the description of the plant with special arrangement
     * @details Returns the base plant description with added special arrangement details
     * @return std::string The enhanced description of the plant
     * @authors Jerusha, Rachel
     */
    std::string getDescription() const override;

    /**
     * @brief Calculates the total price including special arrangement
     * @details Returns the base plant price plus the cost of special arrangement
     * @return double The total price of the decorated plant
     * @authors Jerusha, Rachel
     */
    double getPrice() const override;
};

#endif