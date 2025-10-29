#include "Temperate.h"

#include "PartialSunStrategy.h"
#include "OrganicFertilizer.h"
#include "MediumWaterStrategy.h"

Temperate::Temperate(){
    wS = new MediumWaterStrategy();
    sS = new PartialSunStrategy();
    fS = new OrganicFertilizer();
}
void Temperate::Fertilizing(Plant* p){
    fS->applyFertilizer(p);
}
void Temperate::Watering(Plant* p){
    wS->applyWater(p);
}
void Temperate::Sunlight(Plant* p){
    sS->applySunlight(p);
}
void Temperate::printCareRoutine(){
    std::cout << "\n ================================================= \n";
    std::cout << "This plant uses: \n";
    std::cout << "-Medium Watering care strategy \n";
    std::cout << "-Partial Sunlight care strategy \n";
    std::cout << "-Organic Fertilizing care strategy \n";
}