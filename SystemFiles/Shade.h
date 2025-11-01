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
    WaterStrategy* wS;
    FertilizerStrategy* fS;
    SunlightStrategy* sS;
public:
    Shade();
    void Fertilizing(Plant* p) override;
    void Watering(Plant* p) override;
    void Sunlight(Plant* p) override;
    void printCareRoutine() override;
};

#endif