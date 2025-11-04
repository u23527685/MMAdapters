/**
 * @file InorganicFertilizer.h
 * @brief Concrete strategy for applying inorganic fertilizer to plants.
 *
 * InorganicFertilizer implements the FertilizerStrategy interface to provide
 * a fertilization strategy using synthetic, chemical-based nutrients.
 * This strategy provides quick nutrient release for rapid plant growth.
 *
 * @see FertilizerStrategy
 * @see Plant
 *
 * @author
 * Jay Lopes
 */
#ifndef INORGANICFERTILIZER_H
#define INORGANICFERTILIZER_H

#include "Plant.h"
#include "FertilizerStrategy.h"

/**
 * @class InorganicFertilizer
 * @brief Strategy for applying inorganic fertilizers to a plant.
 */
class  InorganicFertilizer : public FertilizerStrategy{
public:
    /**
     * @brief Applies the inorganic fertilizer strategy to a plant.
     *
     * Increases the nutrient level by 40ppm, capped at the plant’s maximum level.
     *
     * @param p Pointer to the plant being fertilized.
     */
    void applyFertilizer(Plant* p) override;

    /**
     * @brief Gets the name of this fertilizer strategy.
     * @return String representing the strategy name.
     */
    std::string getStrategyName() const override;
};

#endif