#include "SeedlingState.h"
#include <iostream>

#include "DistressedState.h"
#include "MatureState.h"
#include "Plant.h"
#include "PlantCareRoutine.h"
#include "PlantLifeCycle.h"
#include "WitheredState.h"

void SeedlingState::applyCare(PlantLifeCycle *context, Plant *plant,
                              PlantCareRoutine *routine)
{
    if (!routine)
    {
        std::cout << "Error: No care routine provided for " << plant->getName()
                  << "\n";
        return;
    }
    routine->Watering(plant);
    routine->Sunlight(plant);
    routine->Fertilizing(plant);

    plant->increaseGrowthProgress();
    evaluate(context, plant);
}

bool SeedlingState::evaluate(PlantLifeCycle *context, Plant *plant)
{
    bool sunlightOk =
        plant->getCategory() == "Shade"
            ? plant->getCurrentSunlight() >= -10
            : plant->getCurrentSunlight() >= plant->getMinSunlight();
    bool withinMinMax =
        plant->getCurrentWater() >= plant->getMinWater() && sunlightOk &&
        plant->getCurrentNutrients() >= plant->getMinNutrients();

    if (plant->getGrowthProgress() >= 5 && withinMinMax)
    {
        context->setState(std::make_unique<MatureState>()); // triggers notify()
        return true;
    }

    return false;
}
PlantState *SeedlingState::clone() const { return new SeedlingState(); }

std::string SeedlingState::getName() const { return "Seedling"; }
