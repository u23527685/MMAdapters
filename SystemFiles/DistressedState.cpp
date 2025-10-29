#include "DistressedState.h"
#include <iostream>

#include "MatureState.h"
#include "SeedlingState.h"
#include "WitheredState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"

void DistressedState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
    /*
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
                   } */

                   
    if (plant->getCurrentWater() < 30)     routine->Watering(plant);
    if (plant->getCurrentSunlight() < 30)  routine->Sunlight(plant);
    if (plant->getCurrentNutrients() < 30) routine->Fertilizing(plant);

    // After care: check current levels
    int w = plant->getCurrentWater();
    int s = plant->getCurrentSunlight();
    int n = plant->getCurrentNutrients();

    // If any stat drops below 10 → Withered
    if (w < 10 || s < 10 || n < 10) {
        context->setState(new WitheredState());
    }
    // If all stats >= 30 → Recovered to Mature
    else if (w >= 30 && s >= 30 && n >= 30) {
        context->setState(new MatureState());
    }
}

bool DistressedState::evaluate(PlantLifeCycle* context, Plant* plant) {
    /*if (plant->getCurrentWater() < plant->getMinWater() / 2 ||
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

    return false; */


    int w = plant->getCurrentWater();
    int s = plant->getCurrentSunlight();
    int n = plant->getCurrentNutrients();

    if (w < 10 || s < 10 || n < 10) {
        context->setState(new WitheredState());
        return false;
    }
    if (w >= 30 && s >= 30 && n >= 30) {
        context->setState(new MatureState());
        return true;
    }
    return false;
}


std::string DistressedState::getName() const {
    return "Distressed";
}

