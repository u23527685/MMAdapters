/**
 * @file OrganicFertilizer.h
 * @brief Concrete fertilizer strategy using organic nutrients.
 *
 * OrganicFertilizer increases a plant’s nutrient level naturally using
 * organic compounds. It implements the FertilizerStrategy interface.
 *
 * @see FertilizerStrategy
 * @see Plant
 *
 * @author
 * Jay Lopes
 */
#ifndef ORGANICFERTILIZER_H
#define ORGANICFERTILIZER_H

#include "Plant.h"
#include "FertilizerStrategy.h"

/**
 * @class OrganicFertilizer
 * @brief Strategy for applying organic fertilizer to a plant.
 */
class OrganicFertilizer : public FertilizerStrategy{
public:
    /**
     * @brief Applies the organic fertilizer strategy to a plant.
     *
     * Increases nutrient levels by 80 ppm, capped at the plant’s maximum limit.
     * This promotes growth using natural compounds.
     *
     * @param p Pointer to the plant receiving the fertilizer.
     */
    void applyFertilizer(Plant* p) override;

    /**
     * @brief Get the name of this strategy.
     * @return String identifying the strategy type.
     */
    std::string getStrategyName() const override;
};

#endif