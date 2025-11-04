#include "WitheredState.h"
#include "DistressedState.h"
#include "Plant.h"
#include "PlantCareRoutine.h"
#include "PlantLifeCycle.h"
#include <iostream>
/**
 * @file WitheredState.cpp
 * @brief Implementation of the WitheredState class functions
 * @author Isha
 * @date 26 October 2025
 */

/**
 * @brief Implements care routine for a withered plant
 * @details Attempts to apply basic care routines even though the plant is in a
 * terminal state. All care actions are logged but may not affect the plant's
 * state.
 *
 * @param context Pointer to the PlantLifeCycle context
 * @param plant Pointer to the Plant object being cared for
 * @param routine Pointer to the PlantCareRoutine to be applied
 * @throws None
 * @author Isha
 */
void WitheredState::applyCare(PlantLifeCycle *context, Plant *plant,
                              PlantCareRoutine *routine)
{
    // Withered is a terminal state. Log and attempt minimal care, but do NOT
    // change state.
    if (!routine)
    {
        std::cout << "Error: No care routine provided for " << plant->getName()
                  << "\n";
        return;
    }
    std::cout
        << "[Withered State] " << plant->getName()
        << " is withered. Attempting care, but state may remain Withered.\n";

    routine->Watering(plant);
    routine->Sunlight(plant);
    routine->Fertilizing(plant);
    evaluate(context, plant);
}

/**
 * @brief Evaluates the current condition of the withered plant
 * @details Checks if the plant's vital statistics are significantly above
 * minimum requirements, potentially allowing transition to Distressed state if
 * conditions are met
 *
 * @param context Pointer to the PlantLifeCycle context
 * @param plant Pointer to the Plant object being evaluated
 * @return bool Returns false as default, true only if state changes to
 * Distressed
 * @author Isha
 */
bool WitheredState::evaluate(PlantLifeCycle *context, Plant *plant)
{
    double minW = plant->getMinWater();
    double minS = plant->getMinSunlight();
    double minN = plant->getMinNutrients();
    double curW = plant->getCurrentWater();
    double curS = plant->getCurrentSunlight();
    double curN = plant->getCurrentNutrients();

    if (curW >= minW * 2 && curS >= minS * 2 && curN >= minN * 2)
    {
        context->setState(std::make_unique<DistressedState>());
        return false;
    }
    return false;
}
/**
 * @brief Creates a deep copy of the WitheredState object
 * @details Implements the virtual clone method for the WitheredState class
 *
 * @return PlantState* Pointer to a new WitheredState object
 * @author Isha
 */
PlantState *WitheredState::clone() const { return new WitheredState(); }

/**
 * @brief Returns the name of the current state
 * @details Implements the virtual getName method for the WitheredState class
 *
 * @return std::string "Withered" as the state name
 * @author Isha
 */
std::string WitheredState::getName() const { return "Withered"; }