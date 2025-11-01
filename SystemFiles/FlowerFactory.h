#ifndef FLOWERFACTORY_H
#define FLOWERFACTORY_H
#include "PlantFactory.h"
#include "Plant.h"
#include "Rose.h"

class FlowerFactory : public PlantFactory {
public:
    Plant* createPlant(std::string plantType, double price) override;
};

#endif
