#ifndef SEEDSTATE_H
#define SEEDSTATE_H

#include "PlantState.h"

/**
 * @class SeedState
 * @brief Represents the initial state of a plant's life cycle, where it is a
 * seed. In this state, the seed is dormant and requires specific conditions to
 * germinate and grow into a seedling.
 */

class SeedlingState;
class SeedState : public PlantState
{
  public:
    void applyCare(PlantLifeCycle *context, Plant *plant,
                   PlantCareRoutine *routine) override;
    bool evaluate(PlantLifeCycle *context, Plant *plant) override;
    std::string getName() const override;
    PlantState *clone() const override;
};

#endif