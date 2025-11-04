/**
 * @file Sunny.h
 * @brief Plant care routine for sunny conditions.
 *
 * Implements watering, fertilizing, and sunlight strategies suitable for sun-loving plants.
 *
 * @see PlantCareRoutine
 * @see WaterStrategy
 * @see FertilizerStrategy
 * @see SunlightStrategy
 *
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
 * @brief Implements the care routine for sun-loving plants.
 *
 * Provides high sunlight exposure, moderate watering, and rich fertilizing patterns.
 */
class Sunny: public PlantCareRoutine{
    private:
    std::unique_ptr<WaterStrategy> wS; /**< Watering strategy for sunny conditions. */
    std::unique_ptr<SunlightStrategy> sS; /**< Sunlight strategy for sunny conditions. */
    std::unique_ptr<FertilizerStrategy> fS; /**< Fertilizer strategy for sunny conditions. */
public:
    /**
     * @brief Constructs a Sunny care routine with appropriate strategies.
     */
    Sunny();

    /**
     * @brief Applies fertilizing strategy for sunny plants.
     * @param p Pointer to the plant to fertilize.
     */
    void Fertilizing(Plant* p) override;

     /**
     * @brief Applies watering strategy for sunny plants.
     * @param p Pointer to the plant to water.
     */
    void Watering(Plant* p) override;

     /**
     * @brief Applies sunlight strategy for sunny plants.
     * @param p Pointer to the plant to expose to sunlight.
     */
    void Sunlight(Plant* p) override;

    /**
     * @brief Prints the care routine details for debugging or display.
     */
    void printCareRoutine() override;
};

#endif