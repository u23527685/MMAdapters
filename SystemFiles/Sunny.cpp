#include "Sunny.h"

#include "FullSunStrategy.h"
#include "InorganicFertilizer.h"
#include "LowWaterStrategy.h"
#include <memory>

Sunny::Sunny(){
    wS = std::make_unique<LowWaterStrategy>();
    sS = std::make_unique<FullSunStrategy>();
    fS = std::make_unique<InorganicFertilizer>();
}
void Sunny::Fertilizing(Plant* p){
    fS->applyFertilizer(p);
}
void Sunny::Watering(Plant* p){
    wS->applyWater(p);
}
void Sunny::Sunlight(Plant* p){
    sS->applySunlight(p);
}
void Sunny::printCareRoutine(){
    std::cout << "\n ================================================= \n";
    std::cout << "This plant uses: \n";
    std::cout << "-Low Watering care strategy \n";
    std::cout << "-Full Sunlight care strategy \n";
    std::cout << "-Inorganic Fertilizing care strategy \n";
}