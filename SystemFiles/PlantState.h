#ifndef PLANTSTATE_H
#define PLANTSTATE_H

#include "PLantLifeCycle.h"
#include "Plant.h"
#include "PlantCareRoutine.h"
class Plant;
class PlantLifeCycle;
class PlantCareRoutine;
/**
 * @class PlantState
 * @brief Abstract base class representing a state in a plant's life cycle.
 * This class provides a common interface for all plant states, allowing for
 * polymorphic behavior.
 */
class PlantState
{

  public:
    /**
     * @brief Applies care to the plant in this state.
     * @param context The plant's life cycle context.
     * @param plant The plant object being cared for.
     * @param routine The care routine to apply.
     */
    virtual void applyCare(PlantLifeCycle *context, Plant *plant,
                           PlantCareRoutine *routine) = 0;
    /**
     * @brief Evaluates the plant's condition and transitions to another state
     * if necessary.
     * @param context The plant's life cycle context.
     * @param plant The plant object being evaluated.
     * @return True if the plant remains in this state, false otherwise.
     */
    virtual bool evaluate(PlantLifeCycle *context, Plant *plant) = 0;
    /**
     * @brief Gets the name of this state.
     * @return The name of this state.
     */
    virtual std::string getName() const = 0;
    virtual PlantState *clone() const = 0;
    virtual ~PlantState() = default;
};

#endif