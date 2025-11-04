/**
 * @file WitheredState.h
 * @author Rachel
 * @brief Declares the WitheredState class representing a plant’s final life stage.
 */
#ifndef WITHEREDSTATE_H
#define WITHEREDSTATE_H

#include "PlantState.h"

/**
 * @class WitheredState
 * @brief Represents the final state of a plant's life cycle, where it has withered and died.
 * In this state, the plant is beyond recovery and will not respond to care.
 */
class WitheredState : public PlantState {
public:
    /**
     * @brief Attempts to apply care to a withered plant.
     * @param context The plant life cycle context.
     * @param plant The plant that is in the withered state.
     * @param routine The care routine being attempted (has no effect).
     */
    void applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) override;

    /**
     * @brief Evaluates state transitions for a withered plant.
     * @param context The life cycle managing the plant’s state.
     * @param plant The plant being evaluated.
     * @return Always returns false, as withered plants cannot recover.
     */
    bool evaluate(PlantLifeCycle* context, Plant* plant) override;

    /**
     * @brief Retrieves the name of the current state.
     * @return A string representing "Withered State".
     */
    std::string getName() const override;

    /**
     * @brief Creates a clone of this state.
     * @return A pointer to a new WitheredState object.
     */
    PlantState* clone() const override;
};

#endif