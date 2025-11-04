/**
 * @file DistressedState.h
 * @brief Represents the distressed state of a plant's life cycle.
 *
 * The DistressedState class models a condition where a plant is struggling
 * due to insufficient care or environmental factors. With proper care,
 * it may recover and transition to a healthier state.
 *
 * @see PlantState
 * @see PlantLifeCycle
 * @see PlantCareRoutine
 *
 * @autor
 * Isha Kalyan
 */
#ifndef DISTRESSEDSTATE_H
#define DISTRESSEDSTATE_H

#include "PlantCareRoutine.h"
#include "PLantLifeCycle.h"
#include "PlantState.h"

/**
 * @class DistressedState
 * @brief Concrete state representing a plant in distress.
 *
 * In this state, the plant exhibits poor health. Applying the correct care
 * routine may allow it to recover to a normal or thriving state.
 */
class DistressedState : public PlantState {
public:
     /**
     * @brief Apply care to a distressed plant.
     * @param context The lifecycle context controlling state transitions.
     * @param plant Pointer to the affected plant.
     * @param routine The care routine being applied.
     */
    void applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) override;

    /**
     * @brief Evaluate whether the plant remains in distress or recovers.
     * @param context The lifecycle context.
     * @param plant Pointer to the plant being evaluated.
     * @return True if state change occurs, otherwise false.
     */
    bool evaluate(PlantLifeCycle* context, Plant* plant) override;

    /**
     * @brief Retrieve the name of this state.
     * @return String "Distressed".
     */
    std::string getName() const override;

     /**
     * @brief Create a deep copy of this state.
     * @return New DistressedState instance.
     */
    PlantState* clone() const override;
};

#endif