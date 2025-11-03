#include "OrganicFertilizer.h"
#include <iostream>

std::string OrganicFertilizer::getStrategyName() const{
    return "Organic Fertilizer";
}

void OrganicFertilizer::applyFertilizer(Plant* p) {
    std::cout << "Applying Organic Fertilizer to " << p->getName() << ": " << p->getCurrentNutrients() << "ppm → ";
    p->setCurrentNutrients(p->getCurrentNutrients() + 80);
    std::cout << p->getCurrentNutrients() << "ppm (" << (p->getCurrentNutrients() * 100.0 / p->getMaxNutrients()) << "%)\n";
}
