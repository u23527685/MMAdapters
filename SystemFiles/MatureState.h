#ifndef MATURESTATE_H
#define MATURESTATE_H

#include "PlantState.h"

class MatureState : public PlantState {
public:
    MatureState(Plant* ctx) : PlantState(ctx) {}
    void handleGrowth(Plant* plant) override;
    void changeState() override;
    std::string getState() override;
};

#endif