#ifndef FERTILIZERSTRATEGY_H
#define FERTILIZERSTRATEGY_H

#include "Plant.h"

class FertilizerStrategy{
protected:
    Plant* currentPlant;
public:
    virtual void applyFertilizer(Plant* p)=0;
};

#endif