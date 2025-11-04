#ifndef SEEDLINGSTATE_H
#define SEEDLINGSTATE_H

#include "PlantState.h"
/**
 * @class SeedlingState
 * @brief Represents the initial growth stage of a plant's life cycle.
 * In this state, the plant is vulnerable and requires careful nurturing to
 * develop into a healthy mature plant.
 */
class SeedlingState : public PlantState
{
  public:
    void applyCare(PlantLifeCycle *context, Plant *plant,
                   PlantCareRoutine *routine) override;
    bool evaluate(PlantLifeCycle *context, Plant *plant) override;
    std::string getName() const override;
    PlantState *clone() const override;
};

#endif