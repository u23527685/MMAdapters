#ifndef ORGANICFERTILIZER_H
#define ORGANICFERTILIZER_H

#include "Plant.h"
#include "FertilizerStrategy.h"

class OrganicFertilizer : public FertilizerStrategy{
public:
    /**
 * @brief Applies the organic fertilizer strategy to a plant.
 * This method applies the organic fertilizer strategy to the given plant by increasing its nutrient level.
 * @param p The plant to apply the organic fertilizer strategy to.
 * @note The nutrient level is increased by a fixed amount of 80 ppm.
 * @warning This method assumes that the plant's current nutrient level and maximum nutrient level are valid.
 * @note The plant's nurient level will be capped at its maximum water level if the increase exceeds the remaining capacity.
 */
    void applyFertilizer(Plant* p) override;
    std::string getStrategyName() const override;
};

#endif