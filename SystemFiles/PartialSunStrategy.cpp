#include "Plant.h"
#include "PartialSunStrategy.h"
#include <iostream>

std::string PartialSunStrategy::getStrategyName() const{
    return "Partial Sun";
}

void PartialSunStrategy::applySunlight(Plant* p) {
    std::cout << "Applying Partial Sun to " << p->getName() << ": " << p->getCurrentSunlight() << "% → ";
    p->setCurrentSunlight(p->getCurrentSunlight() + 40);
    std::cout << p->getCurrentSunlight() << "% (hrs/day)\n";
}
