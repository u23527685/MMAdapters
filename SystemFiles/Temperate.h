/**
 * @file Temperate.h
 * @brief Header file for the Temperate plant care routine class
 * @author Jay
 * @date October 26, 2025
 */
#ifndef TEMPERATE_H
#define TEMPERATE_H

#include <string>
#include "Plant.h"
#include "PlantCareRoutine.h"
#include "WateringStrategy.h"
#include "FertilizerStrategy.h"
#include "SunlightStrategy.h"
#include <memory>


class Plant;
/**
 * @class Temperate
 * @brief Implements care routine specifically for temperate plants
 * @details Provides specialized care strategies for watering, sunlight, and fertilization
 *          tailored to temperate plant species
 * @author Jay
 */
class Temperate: public PlantCareRoutine{
    private:
    std::unique_ptr<WaterStrategy> wS;
    std::unique_ptr<SunlightStrategy> sS;
    std::unique_ptr<FertilizerStrategy> fS;
public:
    /**
        * @brief Constructor for Temperate care routine
        * @details Initializes the water, sunlight, and fertilizer strategies
        * @return None (constructor)
        * @author Jay
        */
    Temperate();

    /**
        * @brief Applies fertilizer to a temperate plant
        * @details Implements the fertilizing strategy specific to temperate plants
        * @param p Pointer to the Plant object being fertilized
        * @return void
        * @author Jay
        */
    void Fertilizing(Plant* p) override;

      /**
         * @brief Waters a temperate plant
         * @details Implements the watering strategy specific to temperate plants
         * @param p Pointer to the Plant object being watered
         * @return void
         * @author Jay
         */
    void Watering(Plant* p) override;
        /**
         * @brief Manages sunlight exposure for a temperate plant
         * @details Implements the sunlight strategy specific to temperate plants
         * @param p Pointer to the Plant object being given sunlight
         * @return void
         * @author Jay
         */
    void Sunlight(Plant* p) override;

        /**
         * @brief Prints the care routine details
         * @details Displays information about the current care routine settings
         * @return void
         * @author Jay
         */
    void printCareRoutine() override;
};

#endif