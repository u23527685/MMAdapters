#include "WitheredState.h"
#include <iostream>
#include "DistressedState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"

void WitheredState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
    std::cout << "[WitheredState] Plant is withered. Care may be attempted, but recovery is unlikely." << std::endl;

    if (plant->getCurrentWater() < 10) routine->Watering(plant);
    if (plant->getCurrentSunlight() < 10) routine->Sunlight(plant);
    if (plant->getCurrentNutrients() < 10) routine->Fertilizing(plant);
    context->isHealthy();
}

bool WitheredState::evaluate(PlantLifeCycle* context, Plant* plant) {
    return false;
}


std::string WitheredState::getName() const {
    return "Withered";
}