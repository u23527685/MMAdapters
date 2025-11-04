#include "MediumWaterStrategy.h"
#include "Plant.h"
#include <iostream>

std::string MediumWaterStrategy::getStrategyName() const
{
    return "Medium Water";
}

void MediumWaterStrategy::applyWater(Plant *p)
{
    std::cout << "Applying Medium Water to " << p->getName() << ": "
              << p->getCurrentWater() << "ml → ";
    p->setCurrentWater(p->getCurrentWater() + 50);
    std::cout << p->getCurrentWater() << "ml ("
              << (p->getCurrentWater() * 100.0 / p->getMaxWater()) << "%)\n";
}
