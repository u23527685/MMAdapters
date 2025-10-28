#include "SeedState.h"
#include "SeedlingState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"
#include <iostream>

#include "SeedlingState.h"

void SeedState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
    routine->Watering(plant);
    routine->Sunlight(plant);
    routine->Fertilizing(plant);

    if (plant->getCurrentWater() >= 60 &&
        plant->getCurrentSunlight() >= 60 &&
        plant->getCurrentNutrients() >= 60) {
        context->setState(new SeedlingState());
    }
}

bool SeedState::evaluate(PlantLifeCycle* context, Plant* plant) {
    if (plant->getCurrentWater() >= 60 &&
        plant->getCurrentSunlight() >= 60 &&
        plant->getCurrentNutrients() >= 60) {
        context->setState(new SeedlingState());
        return true;
    }
    return false;
}


std::string SeedState::getName() const {
    return "Seed";
}


