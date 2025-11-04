#ifndef INORGANICFERTILIZER_H
#define INORGANICFERTILIZER_H

#include "FertilizerStrategy.h"
#include "Plant.h"

class InorganicFertilizer : public FertilizerStrategy
{
  public:
    /**
     * @brief Applies the inorganic fertilizer strategy to a plant.
     * This method applies the inorganic fertilizer strategy to the given plant
     * by increasing its nutrient level.
     * @param p The plant to apply the inorganic fertilizer strategy to.
     * @note The nutrient level is increased by 40ppm.
     * @note The plant's nutrient level will be capped at its maximum water
     * level if the increase exceeds the remaining capacity.
     */
    void applyFertilizer(Plant *p) override;
    std::string getStrategyName() const override;
};

#endif