#include "WitheredState.h"
#include <iostream>
#include "DistressedState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"

void WitheredState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
    std::cout << "[Withered State] " << plant->getName() << " is withered. Care may be attempted, but recovery is unlikely." << std::endl;

    if (plant->getCurrentWater() < 10) routine->Watering(plant);
    if (plant->getCurrentSunlight() < 10) routine->Sunlight(plant);
    if (plant->getCurrentNutrients() < 10) routine->Fertilizing(plant);
    
    if (plant->getCurrentWater() >= 20 &&
        plant->getCurrentSunlight() >= 20 &&
        plant->getCurrentNutrients() >= 20) {
        context->setState(new DistressedState());
    }
}

bool WitheredState::evaluate(PlantLifeCycle* context, Plant* plant) {
    int w = plant->getCurrentWater();
    int s = plant->getCurrentSunlight();
    int n = plant->getCurrentNutrients();

    // Can only recover to Distressed, not Mature
    if (w >= 20 && s >= 20 && n >= 20) {
        context->setState(new DistressedState());
        return false; // still not healthy
    }
    return false;
}


std::string WitheredState::getName() const {
    return "Withered";
}