#include "InorganicFertilizer.h"
#include <iostream>

std::string InorganicFertilizer::getStrategyName() const{
    return "Inorganic Fertilizer";
}

void InorganicFertilizer::applyFertilizer(Plant* p){
    std::cout << "applying the inorganic fertilizer strategy" << std::endl << "Current Nutrients level: " << p->getCurrentNutrients() << "ppm" <<std::endl;
    std::cout << "Max Nutrients level: " << p->getMaxNutrients() << "ppm" << std::endl << "Nurtient level %: " << ((double)p->getCurrentNutrients()/p->getMaxNutrients())*100 << std::endl;
    std::cout << "Filling " << p->getName() << "with 40ppm of inorganic fertilizer" << std::endl;
    p->setCurrentNutrients(p->getCurrentNutrients() + 40 );
    std::cout << "Current Nutrients level: " << p->getCurrentNutrients() << "ppm" <<std::endl << "Water level %: " << ((double)p->getCurrentNutrients()/p->getMaxNutrients())*100 << std::endl;
}
