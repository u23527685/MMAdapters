#include "MediumWaterStrategy.h"
#include "Plant.h"
#include <iostream>

void MediumWaterStrategy::applyWater(Plant* p){
    std::cout << "applying the Medium Water Strategy" << std::endl << "Current Water level: " << p->getCurrentWater() << "ml" <<std::endl;
    std::cout << "Max Water level: " << p->getMaxWater() << "ml" << std::endl << "Water level %: " << (p->getCurrentWater()/p->getMaxWater())*100 << std::endl;
    std::cout << "Filling " << p->getName() << "with 50ml of water" << std::endl;
    p->setCurrentWater(p->getCurrentWater() + 50);
    std::cout << "Current Water level: " << p->getCurrentWater() << "ml" <<std::endl << "Water level %: " << (p->getCurrentWater()/p->getMaxWater())*100 << std::endl;
}