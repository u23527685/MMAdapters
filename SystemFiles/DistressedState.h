/**
 * @file DistressedState.h
 * @brief Defines the DistressedState class representing a plant's distressed life cycle state.
 */

#ifndef DISTRESSEDSTATE_H
#define DISTRESSEDSTATE_H

#include "PLantLifeCycle.h"
#include "PlantCareRoutine.h"
#include "PlantState.h"

/**
 * @class DistressedState
 * @brief Represents a distressed state of a plant's life cycle.
 *
 * In this state, the plant is struggling to survive due to lack of resources.
 * It will attempt to recover if provided with sufficient care.
 */
class DistressedState : public PlantState {
public:
    /**
     * @brief Applies a care routine to a distressed plant.
     * @param context The current plant life cycle context.
     * @param plant The plant receiving care.
     * @param routine The care routine being applied.
     */
    void applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) override;

    /**
     * @brief Evaluates the current state of the plant to determine if it should transition to another state.
     * @param context The plant life cycle context.
     * @param plant The plant being evaluated.
     * @return True if a state transition is needed, false otherwise.
     */
    bool evaluate(PlantLifeCycle* context, Plant* plant) override;

    /**
     * @brief Retrieves the name of the current state.
     * @return The name of the distressed state.
     */
    std::string getName() const override;

    /**
     * @brief Creates a copy of the current state.
     * @return A pointer to the cloned DistressedState object.
     */
    PlantState* clone() const override;
};

#endif
