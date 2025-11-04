#ifndef TEMPERATE_H
#define TEMPERATE_H

#include "FertilizerStrategy.h"
#include "Plant.h"
#include "PlantCareRoutine.h"
#include "SunlightStrategy.h"
#include "WateringStrategy.h"
#include <memory>
#include <string>

class Plant;

class Temperate : public PlantCareRoutine
{
  private:
    std::unique_ptr<WaterStrategy> wS;
    std::unique_ptr<SunlightStrategy> sS;
    std::unique_ptr<FertilizerStrategy> fS;

  public:
    Temperate();
    void Fertilizing(Plant *p) override;
    void Watering(Plant *p) override;
    void Sunlight(Plant *p) override;
    void printCareRoutine() override;
};

#endif