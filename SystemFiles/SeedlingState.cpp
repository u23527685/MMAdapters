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

    plant->increaseGrowthProgress();

    // grow only based on growthProgress AND ensure current levels are within allowed range
    bool withinMinMax =
        plant->getCurrentWater()  >= plant->getMinWater()  &&
        plant->getCurrentSunlight()>= plant->getMinSunlight()&&
        plant->getCurrentNutrients()>=plant->getMinNutrients();

    if (plant->getGrowthProgress() >= 5 && withinMinMax) {
        context->setState(new MatureState()); // PlantLifeCycle::setState will call notify()
    } else if(!withinMinMax){
        context->setState(new DistressedState());
    } else {
        // Remain in Seedling state
    }
}

bool SeedlingState::evaluate(PlantLifeCycle* context, Plant* plant) {
    // Seedling considered "healthy" (no immediate care needed) only if it has reached growth threshold
    // AND its current levels are within min..max.
    bool withinMinMax =
        plant->getCurrentWater()  >= plant->getMinWater()  &&
        plant->getCurrentSunlight()>= plant->getMinSunlight()&&
        plant->getCurrentNutrients()>=plant->getMinNutrients();

    if (plant->getGrowthProgress() >= 5 && withinMinMax) {
        context->setState(new MatureState()); // triggers notify()
        return true;
    }

    return false;
}


std::string SeedlingState::getName() const {
    return "Seedling";
}
