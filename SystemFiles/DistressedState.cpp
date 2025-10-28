#include "DistressedState.h"
#include <iostream>

#include "MatureState.h"
#include "SeedlingState.h"
#include "WitheredState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"

void DistressedState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
    if (plant->getCurrentWater() < plant->getMinWater()) routine->Watering(plant);
    if (plant->getCurrentSunlight() < plant->getMinSunlight()) routine->Sunlight(plant);
    if (plant->getCurrentNutrients() < plant->getMinNutrients()) routine->Fertilizing(plant);

    if (plant->getCurrentWater() >= plant->getMinWater() &&
        plant->getCurrentSunlight() >= plant->getMinSunlight() &&
        plant->getCurrentNutrients() >= plant->getMinNutrients()) {
        context->setState(new MatureState());
        } else if (plant->getCurrentWater() < plant->getMinWater() / 2 ||
                   plant->getCurrentSunlight() < plant->getMinSunlight() / 2 ||
                   plant->getCurrentNutrients() < plant->getMinNutrients() / 2) {
            context->setState(new WitheredState());
                   }
}

bool DistressedState::evaluate(PlantLifeCycle* context, Plant* plant) {
    if (plant->getCurrentWater() < plant->getMinWater() / 2 ||
        plant->getCurrentSunlight() < plant->getMinSunlight() / 2 ||
        plant->getCurrentNutrients() < plant->getMinNutrients() / 2) {
        context->setState(new WitheredState());
        return false;
        }

    if (plant->getCurrentWater() >= plant->getMinWater() &&
        plant->getCurrentSunlight() >= plant->getMinSunlight() &&
        plant->getCurrentNutrients() >= plant->getMinNutrients()) {
        context->setState(new MatureState());
        return true;
        }

    return false;
}


std::string DistressedState::getName() const {
    return "Distressed";
}

