#include "Plant.h"
#include "FullSunStrategy.h"
#include <iostream>

std::string FullSunStrategy::getStrategyName() const override {
    return "Full Sun";
}

void FullSunStrategy::applySunlight(Plant* p){
    std::cout << "applying the Full Sun strategy" << std::endl << "Current Sunlight level: " << p->getCurrentSunlight() << "% (hrs/day)" <<std::endl;
    std::cout << "Max Sunlight level: " << p->getMaxSunlight() << "% (hrs/day)" << std::endl;
    std::cout << "Putting the " << p->getName() << "in the sun for 8 more hours in the sun" << std::endl;
    p->setCurrentSunlight(p->getCurrentSunlight() + 60 );
    std::cout << "Current Sunlight level: " << p->getCurrentSunlight() << "% (hrs/day)" <<std::endl;
}