#include "MatureState.h"
#include <iostream>

#include "DistressedState.h"
#include "WitheredState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"

void MatureState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
    routine->Watering(plant);
    routine->Sunlight(plant);
    routine->Fertilizing(plant);

    if (plant->getCurrentWater() < plant->getMinWater() ||
          plant->getCurrentSunlight() < plant->getMinSunlight() ||
          plant->getCurrentNutrients() < plant->getMinNutrients()) {
            context->setState(new DistressedState());}
}

bool MatureState::evaluate(PlantLifeCycle* context, Plant* plant) {
    if (plant->getCurrentWater() < plant->getMinWater() ||
        plant->getCurrentSunlight() < plant->getMinSunlight() ||
        plant->getCurrentNutrients() < plant->getMinNutrients()) {
        context->setState(new DistressedState());
        return false;
        }
    return true;
}


std::string MatureState::getName() const {
    return "Mature";
}




