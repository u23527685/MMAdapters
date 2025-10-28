#include "OrganicFertilizer.h"
#include <iostream>

std::string OrganicFertilizer::getStrategyName() const{
    return "Organic Fertilizer";
}

void OrganicFertilizer::applyFertilizer(Plant* p){
    std::cout << "applying the organic fertilizer strategy" << std::endl << "Current Nutrients level: " << p->getCurrentNutrients() << "ppm" <<std::endl;
    std::cout << "Max Nutrients level: " << p->getMaxNutrients() << "ppm" << std::endl << "Nurtient level %: " << (p->getCurrentNutrients()/p->getMaxNutrients())*100 << std::endl;
    std::cout << "Filling " << p->getName() << "with 80ppm of organic fertilizer" << std::endl;
    p->setCurrentNutrients(p->getCurrentNutrients() + 80 );
    std::cout << "Current Nutrients level: " << p->getCurrentNutrients() << "ppm" <<std::endl << "Nutrient level %: " << (p->getCurrentNutrients()/p->getMaxNutrients())*100 << std::endl;
}
