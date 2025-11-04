/**
 * @file Tropical.cpp
 * @brief Implementation of the Tropical plant care routine class
 * @author Jay
 * @date October 27, 2025
 */

#include "Tropical.h"
#include <iostream>

#include "PartialSunStrategy.h"
#include "OrganicFertilizer.h"
#include "MediumWaterStrategy.h"

 /**
 * @brief Constructor for Tropical care routine
 * @details Initializes the strategies for water, sunlight, and fertilizer care
 *          using medium water, partial sun, and organic fertilizer strategies
 * @return None (constructor)
 * @author Jay
 */
Tropical::Tropical(){
    wS = std::make_unique<MediumWaterStrategy>();
    sS = std::make_unique<PartialSunStrategy>();
    fS = std::make_unique<OrganicFertilizer>();
}

/**
 * @brief Applies fertilizer to a tropical plant
 * @details Delegates fertilizer application to the fertilizer strategy
 * @param p Pointer to the Plant object being fertilized
 * @return void
 * @author Jay
 */
void Tropical::Fertilizing(Plant* p){
    fS->applyFertilizer(p);
}

/**
 * @brief Waters a tropical plant
 * @details Delegates watering operation to the water strategy
 * @param p Pointer to the Plant object being watered
 * @return void
 * @author Jay
 */
void Tropical::Watering(Plant* p){
    wS->applyWater(p);
}

/**
 * @brief Manages sunlight exposure for a tropical plant
 * @details Delegates sunlight exposure management to the sunlight strategy
 * @param p Pointer to the Plant object being given sunlight
 * @return void
 * @author Jay
 */
void Tropical::Sunlight(Plant* p){
    sS->applySunlight(p);
}

/**
 * @brief Prints the care routine details
 * @details Displays information about the current care routine settings
 * @return void
 * @author Jay
 */
void Tropical::printCareRoutine(){
    std::cout << "\n ================================================= \n";
    std::cout << "This plant uses: \n";
    std::cout << "-Medium Watering care strategy \n";
    std::cout << "-Partial Sunlight care strategy \n";
    std::cout << "-Organic Fertilizing care strategy \n";
}