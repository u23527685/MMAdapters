/**
 * @file Temperate.h
 * @brief Plant care routine for temperate conditions.
 *
 * Uses strategies for watering, fertilizing, and sunlight optimized for temperate climates.
 *
 * @see PlantCareRoutine
 *
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
 * @brief Implements plant care routine for temperate climate plants.
 */
class Temperate: public PlantCareRoutine{
    private:
    std::unique_ptr<WaterStrategy> wS; /**< Watering strategy. */
    std::unique_ptr<SunlightStrategy> sS; /**< Sunlight strategy. */
    std::unique_ptr<FertilizerStrategy> fS; /**< Fertilizer strategy. */
public:
    /**
     * @brief Constructs a Temperate care routine with balanced strategies.
     */
    Temperate();

    /**
     * @brief Applies fertilizer suitable for temperate plants.
     * @param p Pointer to the plant to fertilize.
     */
    void Fertilizing(Plant* p) override;

    /**
     * @brief Applies watering strategy suitable for temperate plants.
     * @param p Pointer to the plant to water.
     */
    void Watering(Plant* p) override;

    /**
     * @brief Applies sunlight exposure for temperate conditions.
     * @param p Pointer to the plant to expose to sunlight.
     */
    void Sunlight(Plant* p) override;

    /**
     * @brief Displays the care routine summary for temperate plants.
     */
    void printCareRoutine() override;
};

#endif