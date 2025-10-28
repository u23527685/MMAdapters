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