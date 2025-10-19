#ifndef INORGANICFERTILIZER_H
#define INORGANICFERTILIZER_H

#include "Plant.h"
#include "FertilizerStrategy.h"

class  InorganicFertilizer : public FertilizerStrategy{
public:
    void applyFertilizer(Plant* p) override;
};

#endif