#include "Plant.h"
#include "PartialSunStrategy.h"
#include <iostream>

std::string PartialSunStrategy::getStrategyName() const{
    return "Partial Sun";
}

void PartialSunStrategy::applySunlight(Plant* p){
    std::cout << "applying the Partial Sun strategy" << std::endl << "Current Sunlight level: " << p->getCurrentSunlight() << "% (hrs/day)" <<std::endl;
    std::cout << "Max Sunlight level: " << p->getMaxSunlight() << "% (hrs/day)" << std::endl;
    std::cout << "Putting the " << p->getName() << "in the sun for 4 more hours in the sun" << std::endl;
    p->setCurrentSunlight(p->getCurrentSunlight() + 40 );
    std::cout << "Current Sunlight level: " << p->getCurrentNutrients() << "% (hrs/day)" <<std::endl;
}
