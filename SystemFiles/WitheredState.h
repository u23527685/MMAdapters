#ifndef WITHEREDSTATE_H
#define WITHEREDSTATE_H

#include "PlantState.h"

/**
 * @class WitheredState
 * @brief Represents the final state of a plant's life cycle, where it has withered and died.
 * @details In this state, the plant is beyond recovery and will not respond to care.
 * @author Isha
 */
class WitheredState : public PlantState {
public:
    /**
     * @brief Applies care routine to a withered plant
     * @details Since the plant is withered, no care actions will have any effect
     * @param context Pointer to the PlantLifeCycle context
     * @param plant Pointer to the Plant object being cared for
     * @param routine Pointer to the PlantCareRoutine to be applied
     * @author Isha
     */
    void applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) override;

    /**
     * @brief Evaluates the current condition of the withered plant
     * @details Always returns false as the plant cannot recover from withered state
     * @param context Pointer to the PlantLifeCycle context
     * @param plant Pointer to the Plant object being evaluated
     * @return bool Returns false as plant cannot transition from withered state
     * @author Isha
     */
    bool evaluate(PlantLifeCycle* context, Plant* plant) override;

    /**
     * @brief Gets the name of the current state
     * @return std::string Returns "Withered" as the state name
     * @author Isha
     */
    std::string getName() const override;

    /**
     * @brief Creates a deep copy of the WitheredState object
     * @return PlantState* Pointer to a new WitheredState object
     * @author Isha
     */
    PlantState* clone() const override;
};

#endif