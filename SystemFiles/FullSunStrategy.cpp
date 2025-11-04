#include "FullSunStrategy.h"
#include "Plant.h"
#include <iostream>

std::string FullSunStrategy::getStrategyName() const { return "Full Sun"; }

void FullSunStrategy::applySunlight(Plant *p)
{
    std::cout << "Applying Full Sun to " << p->getName() << ": "
              << p->getCurrentSunlight() << "% → ";
    p->setCurrentSunlight(p->getCurrentSunlight() + 60);
    std::cout << p->getCurrentSunlight() << "% (hrs/day)\n";
}