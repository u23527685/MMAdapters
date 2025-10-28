#include "PlantDecorator.h"

PlantDecorator::PlantDecorator(Plant* plant) : plant(plant) {}

PlantDecorator::~PlantDecorator() {
    delete plant;
}

std::string PlantDecorator::getDescription() const {
    return plant->getDescription();
}

double PlantDecorator::getPrice() const {
    return plant->getPrice();
}
