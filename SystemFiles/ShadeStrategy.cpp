#include "Plant.h"
#include "ShadeStrategy.h"
#include <iostream>

void ShadeStrategy::applySunlight(Plant* p){
    std::cout << "applying the shading strategy" << std::endl << "Current Sunlight level: " << p->getCurrentSunlight() << "% (hrs/day)" <<std::endl;
    std::cout << "Max Sunlight level: " << p->getMaxSunlight() << "% (hrs/day)" << std::endl;
    std::cout << "Taking the " << p->getName() << "out of the sun" << std::endl;
    p->setCurrentSunlight(p->getCurrentSunlight() + 0 );
    std::cout << "Current Sunlight level: " << p->getCurrentNutrients() << "% (hrs/day)" <<std::endl;
}