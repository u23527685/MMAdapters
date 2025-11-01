#include "Shade.h"

#include "ShadeStrategy.h"
#include "OrganicFertilizer.h"
#include "LowWaterStrategy.h"
#include <memory>

Shade::Shade(){
    wS = std::make_unique<LowWaterStrategy>();
    sS = std::make_unique<ShadeStrategy>();
    fS = std::make_unique<OrganicFertilizer>();
}
void Shade::Fertilizing(Plant* p){
    fS->applyFertilizer(p);
}
void Shade::Watering(Plant* p){
    wS->applyWater(p);
}
void Shade::Sunlight(Plant* p){
    sS->applySunlight(p);
}
void Shade::printCareRoutine(){
    std::cout << "\n ================================================= \n";
    std::cout << "This plant uses: \n";
    std::cout << "-Low Watering care strategy \n";
    std::cout << "-Shade Sunlight care strategy \n";
    std::cout << "-Organic Fertilizing care strategy \n";
}