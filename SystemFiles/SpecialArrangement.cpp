#include "SpecialArrangement.h"

SpecialArrangement::SpecialArrangement(Plant* plant) : PlantDecorator(plant) {}

std::string SpecialArrangement::getDescription() const {
    return plant->getDescription() + ", Special Arrangement";
}

double SpecialArrangement::getPrice() const {
    return plant->getPrice() + 15.0;
}
