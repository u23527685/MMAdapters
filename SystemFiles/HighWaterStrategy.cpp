#include "HighWaterStrategy.h"
#include "Plant.h"
#include <iostream>


std::string HighWaterStrategy::getStrategyName() const{
    return "High Water";
}

void HighWaterStrategy::applyWater(Plant* p) {
    std::cout << "Applying High Water to " << p->getName() << ": " << p->getCurrentWater() << "ml → ";
    p->setCurrentWater(p->getCurrentWater() + 100);
    std::cout << p->getCurrentWater() << "ml (" << (p->getCurrentWater() * 100.0 / p->getMaxWater()) << "%)\n";
}
