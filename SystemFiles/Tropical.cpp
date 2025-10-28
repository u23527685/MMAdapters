#include "Tropical.h"

#include "PartialSunStrategy.h"
#include "OrganicFertilizer.h"
#include "MediumWaterStrategy.h"

Tropical::Tropical(){
    wS = new MediumWaterStrategy();
    sS = new PartialSunStrategy();
    fS = new OrganicFertilizer();
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