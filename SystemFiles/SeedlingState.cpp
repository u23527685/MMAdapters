#include "SeedlingState.h"
#include <iostream>

#include "DistressedState.h"
#include "MatureState.h"
#include "WitheredState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"

void SeedlingState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
    routine->Watering(plant);
    routine->Sunlight(plant);
    routine->Fertilizing(plant);

    if (plant->getCurrentWater() >= 60 &&
        plant->getCurrentSunlight() >= 60 &&
        plant->getCurrentNutrients() >= 60) {
        context->setState(new MatureState());
    }
}

bool SeedlingState::evaluate(PlantLifeCycle* context, Plant* plant) {
    if (plant->getCurrentWater() >= 60 &&
        plant->getCurrentSunlight() >= 60 &&
        plant->getCurrentNutrients() >= 60) {
        context->setState(new MatureState());
        return true;
    }
    return true; // Still healthy, just not ready to transition
}


std::string SeedlingState::getName() const {
    return "Seedling";
}
