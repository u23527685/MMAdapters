/**
 * @file Tropical.h
 * @brief Declares the Tropical care routine for tropical plant types.
 *
 * This class defines the care strategy for tropical plants by implementing
 * watering, sunlight, and fertilizing strategies suitable for warm, humid climates.
 */
#ifndef TROPICAL_H
#define TROPICAL_H

#include <string>
#include "Plant.h"
#include "PlantCareRoutine.h"
#include "WateringStrategy.h"
#include "FertilizerStrategy.h"
#include "SunlightStrategy.h"
#include <memory>


class Plant;

/**
 * @class Tropical
 * @brief Represents the plant care routine for tropical plants.
 *
 * This class provides specific care methods tailored for tropical plants,
 * including fertilizing, watering, and sunlight exposure.
 */
class Tropical: public PlantCareRoutine{
    private:
    std::unique_ptr<WaterStrategy> wS; /**< Strategy for watering tropical plants. */
    std::unique_ptr<SunlightStrategy> sS; /**< Strategy for sunlight exposure. */
    std::unique_ptr<FertilizerStrategy> fS; /**< Strategy for fertilizing tropical plants. */
public:
    /**
     * @brief Constructs a Tropical care routine with appropriate strategies.
     */
    Tropical();

    /**
     * @brief Applies the fertilizing strategy to the plant.
     * @param p Pointer to the plant receiving fertilization.
     */
    void Fertilizing(Plant* p) override;

    /**
     * @brief Applies the watering strategy to the plant.
     * @param p Pointer to the plant being watered.
     */
    void Watering(Plant* p) override;

    /**
     * @brief Applies the sunlight strategy to the plant.
     * @param p Pointer to the plant receiving sunlight.
     */
    void Sunlight(Plant* p) override;

    /**
     * @brief Prints the current tropical care routine details.
     */
    void printCareRoutine() override;
};

#endif