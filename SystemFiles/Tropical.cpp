#include "Tropical.h"
#include <iostream>

#include "PartialSunStrategy.h"
#include "OrganicFertilizer.h"
#include "MediumWaterStrategy.h"

Tropical::Tropical(){
    wS = std::make_unique<MediumWaterStrategy>();
    sS = std::make_unique<PartialSunStrategy>();
    fS = std::make_unique<OrganicFertilizer>();
}
void Tropical::Fertilizing(Plant* p){
    fS->applyFertilizer(p);
}
void Tropical::Watering(Plant* p){
    wS->applyWater(p);
}
void Tropical::Sunlight(Plant* p){
    sS->applySunlight(p);
}
void Tropical::printCareRoutine(){
    std::cout << "\n ================================================= \n";
    std::cout << "This plant uses: \n";
    std::cout << "-Medium Watering care strategy \n";
    std::cout << "-Partial Sunlight care strategy \n";
    std::cout << "-Organic Fertilizing care strategy \n";
}