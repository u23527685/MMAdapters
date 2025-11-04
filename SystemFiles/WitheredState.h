#ifndef WITHEREDSTATE_H
#define WITHEREDSTATE_H

#include "PlantState.h"
/**
 * @class WitheredState
 * @brief Represents the final state of a plant's life cycle, where it has
 * withered and died. In this state, the plant is beyond recovery and will not
 * respond to care.
 */
class WitheredState : public PlantState
{
  public:
    void applyCare(PlantLifeCycle *context, Plant *plant,
                   PlantCareRoutine *routine) override;
    bool evaluate(PlantLifeCycle *context, Plant *plant) override;
    std::string getName() const override;
    PlantState *clone() const override;
};

#endif