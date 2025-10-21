#ifndef SEEDLINGSTATE_H
#define SEEDLINGSTATE_H

#include "PlantState.h"

class SeedlingState : public PlantState {
public:
   void applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) override;
   bool evaluate(PlantLifeCycle* context, Plant* plant) override;
    std::string getName() const override;
};

#endif