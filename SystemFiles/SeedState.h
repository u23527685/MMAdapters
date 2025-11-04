/**
 * @file SeedState.h
 * @brief Header file for the SeedState class
 * @author Isha
 * @date October 24, 2025
 */

#ifndef SEEDSTATE_H
#define SEEDSTATE_H

#include "PlantState.h"

/**
 * @class SeedState
 * @brief Represents the initial state of a plant's life cycle, where it is a
 * seed
 * @details In this state, the seed is dormant and requires specific conditions
 * to germinate and grow into a seedling
 * @author Isha
 */

class SeedlingState;
class SeedState : public PlantState
{
  public:
    /**
     * @brief Applies care routine to a seed
     * @details Implements care actions specific to seeds, focusing on
     * germination conditions
     * @param context Pointer to the PlantLifeCycle context
     * @param plant Pointer to the Plant object being cared for
     * @param routine Pointer to the PlantCareRoutine to be applied
     * @return void
     * @author Isha
     */
    void applyCare(PlantLifeCycle *context, Plant *plant,
                   PlantCareRoutine *routine) override;

    /**
     * @brief Evaluates if the seed is ready to transition to seedling state
     * @details Checks if conditions are suitable for germination
     * @param context Pointer to the PlantLifeCycle context
     * @param plant Pointer to the Plant object being evaluated
     * @return bool Returns true if seed can transition to seedling state, false
     * otherwise
     * @author Isha
     */
    bool evaluate(PlantLifeCycle *context, Plant *plant) override;

    /**
     * @brief Gets the name of the current state
     * @return std::string Returns "Seed" as the state name
     * @author Isha
     */
    std::string getName() const override;

    /**
     * @brief Creates a deep copy of the SeedState object
     * @return PlantState* Pointer to a new SeedState object
     * @author Isha
     */
    PlantState *clone() const override;
};

#endif