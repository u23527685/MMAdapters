#ifndef MATURESTATE_H
#define MATURESTATE_H

#include "PlantCareRoutine.h"
#include "PLantLifeCycle.h"
#include "PlantState.h"

class MatureState : public PlantState {
public:
     void applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) override;
       bool evaluate(PlantLifeCycle* context, Plant* plant) override;
    std::string getName() const override;
};

#endif