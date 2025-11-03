#include "LowWaterStrategy.h"
#include "Plant.h"
#include <iostream>

std::string LowWaterStrategy::getStrategyName() const{
    return "Low Water";
}

void LowWaterStrategy::applyWater(Plant* p) {
    std::cout << "Applying Low Water to " << p->getName() << ": " << p->getCurrentWater() << "ml → ";
    p->setCurrentWater(p->getCurrentWater() + 20);
    std::cout << p->getCurrentWater() << "ml (" << (p->getCurrentWater() * 100.0 / p->getMaxWater()) << "%)\n";
}