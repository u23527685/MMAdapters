#ifndef SEEDLINGSTATE_H
#define SEEDLINGSTATE_H

#include "PlantState.h"

class SeedlingState : public PlantState {
public:
    SeedlingState(Plant* ctx);
    void handleGrowth(Plant* plant) override;
    void changeState() override;
    std::string getState() override;
};

#endif