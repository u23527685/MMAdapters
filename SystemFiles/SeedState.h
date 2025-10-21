#ifndef SEEDSTATE_H
#define SEEDSTATE_H

#include "PlantState.h"
class SeedlingState;
class SeedState : public PlantState {
public:
 void applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) override;
 bool evaluate(PlantLifeCycle* context, Plant* plant) override;
    std::string getName() const override;
};

#endif