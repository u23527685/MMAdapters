#include "SeedlingState.h"
#include <iostream>

#include "DistressedState.h"
#include "MatureState.h"
#include "WitheredState.h"
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "PlantCareRoutine.h"

void SeedlingState::applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) {
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

bool SeedlingState::evaluate(PlantLifeCycle* context, Plant* plant) {
    // Seedling considered "healthy" (no immediate care needed) only if it has reached growth threshold
    // AND its current levels are within min..max.
    bool withinMinMax =
        plant->getCurrentWater()  >= plant->getMinWater()  &&
        plant->getCurrentSunlight()>= plant->getMinSunlight()&&
        plant->getCurrentNutrients()>=plant->getMinNutrients();

    if (plant->getGrowthProgress() >= 5 && withinMinMax) {
        context->setState(std::make_unique<MatureState>()); // triggers notify()
        return true;
    }

    return false;
}
PlantState* SeedlingState::clone() const  {
    return new SeedlingState();
}

std::string SeedlingState::getName() const {
    return "Seedling";
}
