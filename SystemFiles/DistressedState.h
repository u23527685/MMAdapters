#ifndef DISTRESSEDSTATE_H
#define DISTRESSEDSTATE_H

#include "PlantState.h"

class DistressedState : public PlantState {
public:
    DistressedState(Plant* ctx) : PlantState(ctx) {}
    void handleGrowth(Plant* plant) override;
    void changeState() override;
    std::string getState() override;
};

#endif