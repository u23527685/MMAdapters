#ifndef PLANTCAREROUTINE_H
#define PLANTCAREROUTINE_H

#include <string>
#include "Plant.h"


class Plant;

class PlantCareRoutine{
private:
    PlantCareRoutine* PCR;
public:
    PlantCareRoutine* PlantCare(Plant* p);
    virtual void Fertilizing(Plant* p);
    virtual void Watering(Plant* p);
    virtual void Sunlight(Plant* p);
};

#endif