#include "SeedState.h"
#include "SeedlingState.h"
#include "DistressedState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"
#include <iostream>

#include "SeedlingState.h"

void SeedState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
    if (!routine) {
        std::cout << "Error: No care routine provided for " << plant->getName() << "\n";
        return;
    }
    routine->Watering(plant);
    routine->Sunlight(plant);
    routine->Fertilizing(plant);

    plant->increaseGrowthProgress();
    evaluate(context, plant);
}

bool SeedState::evaluate(PlantLifeCycle* context, Plant* plant) {
    // Seed considered "healthy" (no immediate care needed) only if it has reached growth threshold
    if (plant->getGrowthProgress() >= 3) {
        context->setState(std::make_unique<SeedlingState>()); // triggers notify()
        return true;
    }

    return false;
}

PlantState* SeedState::clone() const  {
    return new SeedState();
}


std::string SeedState::getName() const {
    return "Seed";
}


