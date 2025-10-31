#include "DistressedState.h"
#include <iostream>

#include "MatureState.h"
#include "SeedlingState.h"
#include "WitheredState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"

void DistressedState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
     routine->Watering(plant);
    routine->Sunlight(plant);
    routine->Fertilizing(plant);

    // after applying care, re-evaluate to possibly recover
    evaluate(context, plant);

     /**
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
        **/
}

bool DistressedState::evaluate(PlantLifeCycle* context, Plant* plant) {

double minW = plant->getMinWater();
    double minS = plant->getMinSunlight();
    double minN = plant->getMinNutrients();
    double curW = plant->getCurrentWater();
    double curS = plant->getCurrentSunlight();
    double curN = plant->getCurrentNutrients();

    // If any dropped below min -> Withered
    if (curW < minW || curS < minS || curN < minN) {
        context->setState(new WitheredState());
        return false;
    }

    // If recovered to healthy mature thresholds -> Mature
    double healthyWThreshold = minW * 1.2;
    double healthySThreshold = minS * 1.2;
    double healthyNThreshold = minN * 1.2;

    if (curW >= healthyWThreshold && curS >= healthySThreshold && curN >= healthyNThreshold && plant->getGrowthProgress() >= 5) {
        context->setState(new MatureState());
        return true;
    } else if (curW >= healthyWThreshold && curS >= healthySThreshold && curN >= healthyNThreshold && plant->getGrowthProgress() < 5) {
        context->setState(new SeedlingState());
        return true;
    }

    // still distressed (not healthy)
    return false;
}


std::string DistressedState::getName() const {
    return "Distressed";
}

