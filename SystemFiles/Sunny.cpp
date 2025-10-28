#include "Sunny.h"

#include "FullSunStrategy.h"
#include "InorganicFertilizer.h"
#include "LowWaterStrategy.h"

Sunny::Sunny(){
    wS = new LowWaterStrategy();
    sS = new FullSunStrategy();
    fS = new InorganicFertilizer();
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