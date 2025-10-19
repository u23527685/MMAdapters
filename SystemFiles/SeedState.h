#ifndef SEEDSTATE_H
#define SEEDSTATE_H

#include "PlantState.h"
class SeedlingState;
class SeedState : public PlantState {
public:
    SeedState(Plant* ctx);
    void handleGrowth(Plant* plant) override;
    void changeState() override;
    std::string getState() override;
};

#endif