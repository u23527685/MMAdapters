#include "HighWaterStrategy.h"
#include "Plant.h"
#include <iostream>


std::string HighWaterStrategy::getStrategyName() const{
    return "High Water";
}

void HighWaterStrategy::applyWater(Plant* p){
    std::cout << "applying the High Water Strategy" << std::endl << "Current Water level: " << p->getCurrentWater() << "ml" <<std::endl;
    std::cout << "Max Water level: " << p->getMaxWater() << "ml" << std::endl << "Water level %: " << (p->getCurrentWater()/p->getMaxWater())*100 << std::endl;
    std::cout << "Filling " << p->getName() << "with 100ml of water" << std::endl;
    p->setCurrentWater(p->getCurrentWater() + 100 );
    std::cout << "Current Water level: " << p->getCurrentWater() << "ml" <<std::endl << "Water level %: " << (p->getCurrentWater()/p->getMaxWater())*100 << std::endl;
}
