/**
 * @file Sunny.h
 * @brief Header file for the Sunny plant care routine class
 * @author Jay
 * @date October 27, 2025
 */

#ifndef SUNNY_H
#define SUNNY_H

#include <string>
#include "Plant.h"
#include "PlantCareRoutine.h"
#include "WateringStrategy.h"
#include "FertilizerStrategy.h"
#include "SunlightStrategy.h"

class Plant;

/**
 * @class Sunny
 * @brief Implements care routine specifically for sun-loving plants
 * @details Provides specialized care strategies for watering, sunlight, and fertilization
 *          tailored to plants that thrive in sunny conditions
 * @author Jay
 */
class Sunny: public PlantCareRoutine {
    private:
        std::unique_ptr<WaterStrategy> wS;     
        std::unique_ptr<SunlightStrategy> sS;   
        std::unique_ptr<FertilizerStrategy> fS; 

    public:
        /**
         * @brief Constructor for Sunny care routine
         * @details Initializes the water, sunlight, and fertilizer strategies
         * @return None (constructor)
         * @author Jay
         */
        Sunny();

        /**
         * @brief Applies fertilizer to a sun-loving plant
         * @details Implements the fertilizing strategy specific to plants in sunny conditions
         * @param p Pointer to the Plant object being fertilized
         * @return void
         * @author Jay
         */
        void Fertilizing(Plant* p) override;

        /**
         * @brief Waters a sun-loving plant
         * @details Implements the watering strategy specific to plants in sunny conditions
         * @param p Pointer to the Plant object being watered
         * @return void
         * @author Jay
         */
        void Watering(Plant* p) override;

        /**
         * @brief Manages sunlight exposure for a sun-loving plant
         * @details Implements the sunlight strategy specific to plants in sunny conditions
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