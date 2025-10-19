#include "MatureState.h"
#include <iostream>

#include "DistressedState.h"
#include "WitheredState.h"

void MatureState::handleGrowth(Plant* plant) {
    std::cout << "[Mature] " << plant->getName() << " is maintaining maturity, ready for sale." << std::endl;
    changeState();
}

void MatureState::changeState()
{
    if (context->getCurrentWater() < 20 || context->getCurrentSunlight() < 20 || context->getCurrentNutrients() < 20) {
        if (context->getCurrentWater() < 10 || context->getCurrentSunlight() < 10 || context->getCurrentNutrients() < 10) {
            std::cout << "[MatureState] " << context->getName() << " has withered, transitioning to WitheredState." << std::endl;
            context->setState(new WitheredState(context));
        } else {
            std::cout << "[MatureState] " << context->getName() << " is distressed, transitioning to DistressedState." << std::endl;
            context->setState(new DistressedState(context));
        }
    }
}

std::string MatureState::getState()
{
    return "Mature";
}




