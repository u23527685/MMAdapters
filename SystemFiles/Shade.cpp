#include "Shade.h"

#include "ShadeStrategy.h"
#include "OrganicFertilizer.h"
#include "LowWaterStrategy.h"

Shade::Shade(){
    wS = new LowWaterStrategy();
    sS = new ShadeStrategy();
    fS = new OrganicFertilizer();
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