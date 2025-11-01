#ifndef TREEFACTORY_H
#define TREEFACTORY_H
#include "PlantFactory.h"
#include "Plant.h"
#include "Oak.h"

class TreeFactory : public PlantFactory {
public:
    Plant* createPlant(std::string plantType, double price) override;
};

#endif
