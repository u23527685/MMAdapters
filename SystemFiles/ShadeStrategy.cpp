#include "ShadeStrategy.h"
#include "Plant.h"
#include <iostream>

std::string ShadeStrategy::getStrategyName() const { return "Shade"; }

void ShadeStrategy::applySunlight(Plant *p)
{
    std::cout << "Applying Shade to " << p->getName() << ": "
              << p->getCurrentSunlight() << "% → ";
    p->setCurrentSunlight(0);
    std::cout << p->getCurrentSunlight() << "% (hrs/day)\n";
}
