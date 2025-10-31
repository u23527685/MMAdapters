#include "WitheredState.h"
#include <iostream>
#include "DistressedState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"

void WitheredState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
    // Withered is a terminal state. Log and attempt minimal care, but do NOT change state.
    std::cout << "[Withered State] " << plant->getName()
              << " is withered and cannot be recovered. Care may be attempted but state will remain Withered."
              << std::endl;

    // Attempt to bring levels up as best-effort (no state transition).
    if (plant->getCurrentWater() < plant->getMaxWater()) {
        routine->Watering(plant);
    }
    if (plant->getCurrentSunlight() < plant->getMaxSunlight()) {
        routine->Sunlight(plant);
    }
    if (plant->getCurrentNutrients() < plant->getMaxNutrients()) {
        routine->Fertilizing(plant);
    }
}

bool WitheredState::evaluate(PlantLifeCycle* context, Plant* plant) {
    /**
    int w = plant->getCurrentWater();
    int s = plant->getCurrentSunlight();
    int n = plant->getCurrentNutrients();

    // Can only recover to Distressed, not Mature
    if (w >= 20 && s >= 20 && n >= 20) {
        context->setState(new DistressedState());
        return false; // still not healthy
    }
        **/
    return false;
}


std::string WitheredState::getName() const {
    return "Withered";
}