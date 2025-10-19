#ifndef PLANTSTATE_H
#define PLANTSTATE_H

#include "Plant.h"
class Plant;
class PlantState {
protected:
    Plant* context;  // Context is Plant
public:
    PlantState(Plant* ctx) : context(ctx) {}
    virtual ~PlantState() = default;

    virtual void handleGrowth(Plant* plant) = 0;  // Manage growth and transitions
    virtual void changeState() = 0;
    virtual std::string getState() = 0;
};

#endif