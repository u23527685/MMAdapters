#ifndef PLANTCAREROUTINE_H
#define PLANTCAREROUTINE_H

#include "Plant.h"
#include <iostream>
#include <memory>
#include <string>

class Plant;

class PlantCareRoutine
{
  public:
    virtual ~PlantCareRoutine() = default;
    static std::unique_ptr<PlantCareRoutine> PlantCare(Plant *p);
    virtual void Fertilizing(Plant *p) = 0;
    virtual void Watering(Plant *p) = 0;
    virtual void Sunlight(Plant *p) = 0;
    virtual void printCareRoutine() = 0;
};

#endif