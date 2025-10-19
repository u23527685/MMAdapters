#include "SeedState.h"
#include <iostream>

#include "SeedlingState.h"

SeedState::SeedState(Plant* ctx) : PlantState(ctx){
}

void SeedState::handleGrowth(Plant* plant) {
    std::cout << "[Seed] "<< plant->getName() << " is in seed phase, awaiting germination." << std::endl;
    changeState();
}

void SeedState::changeState(){
    if (context->getCurrentWater() >= 40 && context->getCurrentSunlight() >= 40 && context->getCurrentNutrients() >= 40) {
        std::cout << "[SeedState] Germination successful for " << context->getName() << ", transitioning to SeedlingState." << std::endl;
        context->setState(new SeedlingState(context));
    }
}

std::string SeedState::getState()
{
    return "Seed";
}


