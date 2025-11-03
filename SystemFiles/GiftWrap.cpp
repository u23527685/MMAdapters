#include "GiftWrap.h"

GiftWrap::GiftWrap(Plant* plant) : PlantDecorator(plant) {}

std::string GiftWrap::getDescription() const {
    return plant->getDescription() + ", Gift Wrapped";
}

double GiftWrap::getPrice() const {
    return plant->getPrice() + 5.0;
}
