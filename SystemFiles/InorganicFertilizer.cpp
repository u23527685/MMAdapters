#include "InorganicFertilizer.h"
#include <iostream>

std::string InorganicFertilizer::getStrategyName() const{
    return "Inorganic Fertilizer";
}

void InorganicFertilizer::applyFertilizer(Plant* p) {
    std::cout << "Applying Inorganic Fertilizer to " << p->getName() << ": " << p->getCurrentNutrients() << "ppm → ";
    p->setCurrentNutrients(p->getCurrentNutrients() + 40);
    std::cout << p->getCurrentNutrients() << "ppm (" << (p->getCurrentNutrients() * 100.0 / p->getMaxNutrients()) << "%)\n";
}
