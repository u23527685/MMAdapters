#include "BasePlant.h"

BasePlant::BasePlant() : Plant(0, "Basic Plant") {}

BasePlant::BasePlant(double p, std::string desc) : Plant(p, desc) {}


std::string BasePlant::getDescription() const {
    return Plant::getDescription();   
}

double BasePlant::getPrice() const {
    return Plant::getPrice();       
}
