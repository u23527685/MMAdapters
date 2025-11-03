#include "Temperate.h"

#include "FullSunStrategy.h"
#include "InorganicFertilizer.h"
#include "LowWaterStrategy.h"

Temperate::Temperate(){
    wS = std::make_unique<LowWaterStrategy>();
    sS = std::make_unique<FullSunStrategy>();
    fS = std::make_unique<InorganicFertilizer>();
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