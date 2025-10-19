#include "WitheredState.h"
#include <iostream>

void WitheredState::handleGrowth(Plant* plant) {
    std::cout << "[WitheredState] " << plant->getName() << " has withered and died, no further growth possible." << std::endl;
    // No transitions, final state
}

std::string WitheredState::getState()
{
    return "Withered";
}

void WitheredState::changeState(){}
