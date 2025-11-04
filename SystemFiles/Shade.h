/**
 * @file Shade.h
 * @brief Plant care routine implementing shade care.
 *
 * The Shade routine applies watering, fertilizing, and sunlight
 * strategies suitable for shade-tolerant plants.
 *
 * @see PlantCareRoutine
 * @see WateringStrategy
 * @see FertilizerStrategy
 * @see SunlightStrategy
 *
 */
#ifndef SHADE_H
#define SHADE_H

#include <string>
#include "Plant.h"
#include "PlantCareRoutine.h"
#include "WateringStrategy.h"
#include "FertilizerStrategy.h"
#include "SunlightStrategy.h"


class Plant;

class Shade: public PlantCareRoutine{
    private:
    std::unique_ptr<WaterStrategy> wS;
    std::unique_ptr<SunlightStrategy> sS;
    std::unique_ptr<FertilizerStrategy> fS;
public:
    Shade();
    void Fertilizing(Plant* p) override;
    void Watering(Plant* p) override;
    void Sunlight(Plant* p) override;
    void printCareRoutine() override;
};

#endif