#ifndef MATURESTATE_H
#define MATURESTATE_H

#include "PLantLifeCycle.h"
#include "PlantCareRoutine.h"
#include "PlantState.h"
/**
 * @class MatureState
 * @brief Represents a mature state of a plant's life cycle.
 * In this state, the plant is healthy and thriving, and can benefit from
 * regular care. If the plant's resources fall below the minimum required, it
 * will transition to the DistressedState.
 */
class MatureState : public PlantState
{
  public:
    void applyCare(PlantLifeCycle *context, Plant *plant,
                   PlantCareRoutine *routine) override;
    bool evaluate(PlantLifeCycle *context, Plant *plant) override;
    std::string getName() const override;
    PlantState *clone() const override;
};

#endif