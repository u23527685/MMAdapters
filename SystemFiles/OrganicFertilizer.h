#ifndef ORGANICFERTILIZER_H
#define ORGANICFERTILIZER_H

#include "Plant.h"
#include "FertilizerStrategy.h"

class OrganicFertilizer : public FertilizerStrategy{
public:
    void applyFertilizer(Plant* p) override;
};

#endif