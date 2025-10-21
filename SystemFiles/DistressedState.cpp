#include "DistressedState.h"
#include <iostream>

#include "MatureState.h"
#include "SeedlingState.h"
#include "WitheredState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"

void DistressedState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
    if (plant->getCurrentWater() < 20) routine->Watering(plant);
    if (plant->getCurrentSunlight() < 20) routine->Sunlight(plant);
    if (plant->getCurrentNutrients() < 20) routine->Fertilizing(plant);

    if (plant->getCurrentWater() >= 20 &&
        plant->getCurrentSunlight() >= 20 &&
        plant->getCurrentNutrients() >= 20) {
        context->setState(new MatureState());
    } else if (plant->getCurrentWater() < 10 ||
               plant->getCurrentSunlight() < 10 ||
               plant->getCurrentNutrients() < 10) {
        context->setState(new WitheredState());
    }
}

bool DistressedState::evaluate(PlantLifeCycle* context, Plant* plant) {
    if (plant->getCurrentWater() < 10 ||
        plant->getCurrentSunlight() < 10 ||
        plant->getCurrentNutrients() < 10) {
        context->setState(new WitheredState());
        return false;
    }

    if (plant->getCurrentWater() >= 20 &&
        plant->getCurrentSunlight() >= 20 &&
        plant->getCurrentNutrients() >= 20) {
        context->setState(new MatureState());
        return true;
    }

    return false;
}


std::string DistressedState::getName() const {
    return "Distressed";
}

