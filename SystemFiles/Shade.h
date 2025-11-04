/**
 * @file Shade.h
 * @brief Header file for the Shade plant care routine class
 * @date October 27, 2025
 */

#ifndef SHADE_H
#define SHADE_H

#include "FertilizerStrategy.h"
#include "Plant.h"
#include "PlantCareRoutine.h"
#include "SunlightStrategy.h"
#include "WateringStrategy.h"

class Plant;

/**
 * @class Shade
 * @brief Implements care routine specifically for shade-loving plants
 * @details Provides specialized care strategies for watering, sunlight, and
 * fertilization tailored to plants that thrive in shaded conditions
 */
class Shade: public PlantCareRoutine {
    private:
        std::unique_ptr<WateringStrategy> wS;    
        std::unique_ptr<SunlightStrategy> sS;  
        std::unique_ptr<FertilizerStrategy> fS; 

  public:
    /**
     * @brief Constructor for Shade care routine
     * @details Initializes the water, sunlight, and fertilizer strategies
     * @return None (constructor)
     */
    Shade();

    /**
     * @brief Applies fertilizer to a shade-loving plant
     * @details Implements the fertilizing strategy specific to plants in shaded
     * conditions
     * @param p Pointer to the Plant object being fertilized
     * @return void
     */
    void Fertilizing(Plant *p) override;

    /**
     * @brief Waters a shade-loving plant
     * @details Implements the watering strategy specific to plants in shaded
     * conditions
     * @param p Pointer to the Plant object being watered
     * @return void
     */
    void Watering(Plant *p) override;

    /**
     * @brief Manages sunlight exposure for a shade-loving plant
     * @details Implements the sunlight strategy specific to plants in shaded
     * conditions
     * @param p Pointer to the Plant object being given sunlight
     * @return void
     */
    void Sunlight(Plant *p) override;

    /**
     * @brief Prints the care routine details
     * @details Displays information about the current care routine settings
     * @return void
     */
    void printCareRoutine() override;
};

#endif