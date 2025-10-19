#include "DistressedState.h"
#include <iostream>

#include "MatureState.h"
#include "SeedlingState.h"
#include "WitheredState.h"

void DistressedState::handleGrowth(Plant* plant) {
    std::cout << "[DistressedState] " << plant->getName() << " is unhealthy, at risk of withering." << std::endl;
    changeState();
}

void DistressedState::changeState()
{
    if (context->getCurrentWater() >= 20 && context->getCurrentSunlight() >= 20 && context->getCurrentNutrients() >= 20) {
        if (context->getCurrentState() == "Seedling") {
            std::cout << "[DistressedState] " << context->getName() << " has recovered, transitioning to SeedlingState." << std::endl;
            context->setState(new SeedlingState(context));
        } else {
            std::cout << "[DistressedState] " << context->getName() << " has recovered, transitioning to MatureState." << std::endl;
            context->setState(new MatureState(context));
        }
    } else if (context->getCurrentWater() < 10 || context->getCurrentSunlight() < 10 || context->getCurrentNutrients() < 10) {
        std::cout << "[DistressedState] " << context->getName() << " has withered, transitioning to WitheredState." << std::endl;
        context->setState(new WitheredState(context));
    }
}

std::string DistressedState::getState()
{
    return "Disressed";
}

