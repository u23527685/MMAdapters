/**
 * @file SeedlingState.h
 * @brief Header file for the SeedlingState class
 * @date October 27, 2025
 */

#ifndef SEEDLINGSTATE_H
#define SEEDLINGSTATE_H

#include "PlantState.h"

/**
 * @class SeedlingState
 * @brief Represents the initial growth stage of a plant's life cycle
 * @details In this state, the plant is vulnerable and requires careful nurturing 
 *          to develop into a healthy mature plant
 */
class SeedlingState : public PlantState {
public:
    /**
     * @brief Applies care routine to a seedling
     * @details Implements care actions specific to seedlings, focusing on early growth needs
     * @param context Pointer to the PlantLifeCycle context
     * @param plant Pointer to the Plant object being cared for
     * @param routine Pointer to the PlantCareRoutine to be applied
     * @return void
     */
    void applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) override;

    /**
     * @brief Evaluates if the seedling is ready to transition to mature state
     * @details Checks if conditions and growth are suitable for advancement
     * @param context Pointer to the PlantLifeCycle context
     * @param plant Pointer to the Plant object being evaluated
     * @return bool Returns true if seedling can transition to mature state, false otherwise
     */
    bool evaluate(PlantLifeCycle* context, Plant* plant) override;

    /**
     * @brief Gets the name of the current state
     * @return std::string Returns "Seedling" as the state name
     */
    std::string getName() const override;

    /**
     * @brief Creates a deep copy of the SeedlingState object
     * @return PlantState* Pointer to a new SeedlingState object
     */
    PlantState* clone() const override;
};

#endif