#ifndef PLANTSTATE_H
#define PLANTSTATE_H

#include "Plant.h"
#include "PlantCareRoutine.h"
#include "PLantLifeCycle.h"
class Plant;
class PlantLifeCycle;
class PlantCareRoutine;

class PlantState {

public:
    virtual void applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) = 0;
    virtual bool evaluate(PlantLifeCycle* context, Plant* plant) = 0;
    virtual std::string getName() const = 0;
    virtual ~PlantState() {}
};

#endif