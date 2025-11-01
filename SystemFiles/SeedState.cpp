#include "SeedState.h"
#include "SeedlingState.h"
#include "DistressedState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"
#include <iostream>

#include "SeedlingState.h"

void SeedState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
    routine->Watering(plant);
    routine->Sunlight(plant);
    routine->Fertilizing(plant);

    plant->increaseGrowthProgress();

    // grow only based on growthProgress AND ensure current levels are within allowed range

    if (plant->getGrowthProgress() >= 3) {
        context->setState(new SeedlingState()); // PlantLifeCycle::setState will call notify()
    }
}

bool SeedState::evaluate(PlantLifeCycle* context, Plant* plant) {
    // Seed considered "healthy" (no immediate care needed) only if it has reached growth threshold
    if (plant->getGrowthProgress() >= 3) {
        context->setState(new SeedlingState()); // triggers notify()
        return true;
    }

    return false;
}


std::string SeedState::getName() const {
    return "Seed";
}


