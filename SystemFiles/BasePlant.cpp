#include "BasePlant.h"

BasePlant::BasePlant() : Plant(20.0, "Basic Plant") {}

BasePlant::BasePlant(double p, std::string desc) : Plant(p, desc) {}

std::string BasePlant::getDescription() const {
    return "Basic Plant";
}

double BasePlant::getPrice() const {
    return 20.0;
}

