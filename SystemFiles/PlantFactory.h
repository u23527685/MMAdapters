#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H
#include "Plant.h"

class PlantFactory {
public:
    virtual Plant* createPlant(std::string plantType, double price) = 0;
    virtual ~PlantFactory() {}
};

#endif
