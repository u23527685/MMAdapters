#include "LowWaterStrategy.h"
#include "Plant.h"
#include <iostream>

std::string LowWaterStrategy::getStrategyName() const{
    return "Low Water";
}

void LowWaterStrategy::applyWater(Plant* p){
    std::cout << "applying the Low Water Strategy" << std::endl << "Current Water level: " << p->getCurrentWater() << "ml" <<std::endl;
    std::cout << "Max Water level: " << p->getMaxWater() << "ml" << std::endl << "Water level %: " << ((double)p->getCurrentWater()/p->getMaxWater())*100 << std::endl;
    std::cout << "Filling " << p->getName() << " with 20ml of water" << std::endl;
    p->setCurrentWater(p->getCurrentWater() + 20);
    std::cout << "Current Water level: " << p->getCurrentWater() << "ml" <<std::endl << "Water level %: " << ((double)p->getCurrentWater()/p->getMaxWater())*100 << std::endl;
}
