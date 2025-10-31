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

    evaluate(context, plant);
}

bool MatureState::evaluate(PlantLifeCycle* context, Plant* plant) {
    double minW = plant->getMinWater();
    double minS = plant->getMinSunlight();
    double minN = plant->getMinNutrients();
    double curW = plant->getCurrentWater();
    double curS = plant->getCurrentSunlight();
    double curN = plant->getCurrentNutrients();

    // Withered if any resource < min
    if (curW < minW || curS < minS || curN < minN) {
        context->setState(new WitheredState());
        return false;
    }

    // Distressed if any resource == min
    if (curW == minW || curS == minS || curN == minN) {
        context->setState(new DistressedState());
        return false;
    }

    // Healthy mature when each resource >= 120% of min and <= max
    double healthyWThreshold = minW * 1.2;
    double healthySThreshold = minS * 1.2;
    double healthyNThreshold = minN * 1.2;

    bool wGood = (curW >= healthyWThreshold && curW <= plant->getMaxWater());
    bool sGood = (curS >= healthySThreshold && curS <= plant->getMaxSunlight());
    bool nGood = (curN >= healthyNThreshold && curN <= plant->getMaxNutrients());

    return (wGood && sGood && nGood);
}


std::string MatureState::getName() const {
    return "Mature";
}




