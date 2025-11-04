#ifndef TROPICAL_H
#define TROPICAL_H

#include "FertilizerStrategy.h"
#include "Plant.h"
#include "PlantCareRoutine.h"
#include "SunlightStrategy.h"
#include "WateringStrategy.h"
#include <memory>
#include <string>

class Plant;

/**
 * @class Tropical
 * @brief Implements care routine specifically for tropical plants
 * @details Provides specialized care strategies for watering, sunlight, and
 * fertilization tailored to tropical plant species
 * @author Jay
 */
class Tropical : public PlantCareRoutine
{
  private:
    std::unique_ptr<WaterStrategy> wS;
    std::unique_ptr<SunlightStrategy> sS;
    std::unique_ptr<FertilizerStrategy> fS;

  public:
    /**
     * @brief Constructor for Tropical care routine
     * @details Initializes the water, sunlight, and fertilizer strategies
     * @author Jay
     */
    Tropical();

    /**
     * @brief Applies fertilizer to a tropical plant
     * @details Implements the fertilizing strategy specific to tropical plants
     * @param p Pointer to the Plant object being fertilized
     * @author Jay
     */
    void Fertilizing(Plant *p) override;

    /**
     * @brief Waters a tropical plant
     * @details Implements the watering strategy specific to tropical plants
     * @param p Pointer to the Plant object being watered
     * @author Jay
     */
    void Watering(Plant *p) override;

    /**
     * @brief Manages sunlight exposure for a tropical plant
     * @details Implements the sunlight strategy specific to tropical plants
     * @param p Pointer to the Plant object being given sunlight
     * @author Jay
     */
    void Sunlight(Plant *p) override;

    /**
     * @brief Prints the care routine details
     * @details Displays information about the current care routine settings
     * @author Jay
     */
    void printCareRoutine() override;
};

#endif