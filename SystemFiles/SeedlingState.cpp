#include "SeedlingState.h"
#include <iostream>

#include "DistressedState.h"
#include "MatureState.h"
#include "WitheredState.h"

SeedlingState::SeedlingState(Plant* ctx): PlantState(ctx){}

void SeedlingState::changeState()
{
    if (context->getCurrentWater() < 20 || context->getCurrentSunlight() < 20 || context->getCurrentNutrients() < 20) {
        if (context->getCurrentWater() < 10 || context->getCurrentSunlight() < 10 || context->getCurrentNutrients() < 10) {
            std::cout << "[SeedlingState] " << context->getName() << " has withered, transitioning to WitheredState." << std::endl;
            context->setState(new WitheredState(context));
        } else {
            std::cout << "[SeedlingState] " << context->getName() << " is distressed, transitioning to DistressedState." << std::endl;
            context->setState(new DistressedState(context));
        }
    } else if (context->getCurrentWater() >= 60 && context->getCurrentSunlight() >= 60 && context->getCurrentNutrients() >= 60) {
        std::cout << "[SeedlingState] " << context->getName() << " has matured, transitioning to MatureState." << std::endl;
        context->setState(new MatureState(context));
    }
}

void SeedlingState::handleGrowth(Plant* plant)
{
    std::cout << "[Seedling] " << plant->getName() << " is growing toward maturity." << std::endl;
    changeState();
}

std::string SeedlingState::getState()
{
    return "Seedling";
}
