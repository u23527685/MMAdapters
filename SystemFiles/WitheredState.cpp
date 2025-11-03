#include "WitheredState.h"
#include <iostream>
#include "DistressedState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"

void WitheredState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
    // Withered is a terminal state. Log and attempt minimal care, but do NOT change state.
    if (!routine) {
        std::cout << "Error: No care routine provided for " << plant->getName() << "\n";
        return;
    }
    std::cout << "[Withered State] " << plant->getName()
              << " is withered. Attempting care, but state may remain Withered.\n";

    routine->Watering(plant);
    routine->Sunlight(plant);
    routine->Fertilizing(plant);
    evaluate(context, plant);
}

bool WitheredState::evaluate(PlantLifeCycle* context, Plant* plant) {
    double minW = plant->getMinWater();
    double minS = plant->getMinSunlight();
    double minN = plant->getMinNutrients();
    double curW = plant->getCurrentWater();
    double curS = plant->getCurrentSunlight();
    double curN = plant->getCurrentNutrients();

    if (curW >= minW * 2 && curS >= minS * 2 && curN >= minN * 2) {
        context->setState(std::make_unique<DistressedState>());
        return false;
    }
    return false;
}

PlantState* WitheredState::clone() const{
    return new WitheredState();
}


std::string WitheredState::getName() const {
    return "Withered";
}