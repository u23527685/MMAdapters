#include "DecorativePot.h"

DecorativePot::DecorativePot(Plant* plant) : PlantDecorator(plant) {}

std::string DecorativePot::getDescription() const {
    return plant->getDescription() + ", Decorative Pot";
}

double DecorativePot::getPrice() const {
    return plant->getPrice() + 10.0;
}
