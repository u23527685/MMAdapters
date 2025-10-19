#ifndef WITHEREDSTATE_H
#define WITHEREDSTATE_H

#include "PlantState.h"

class WitheredState : public PlantState {
public:
    WitheredState(Plant* ctx) : PlantState(ctx) {}
    void handleGrowth(Plant* plant) override;
    void changeState() override;
    std::string getState() override;
};

#endif