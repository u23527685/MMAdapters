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
class DistressedState : public PlantState
{
  public:
    void applyCare(PlantLifeCycle *context, Plant *plant,
                   PlantCareRoutine *routine) override;
    bool evaluate(PlantLifeCycle *context, Plant *plant) override;
    std::string getName() const override;
    PlantState *clone() const override;
};

#endif
