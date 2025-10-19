#include "Plant.h"

Plant::Plant(std::string name){
    this->name = name;
}

Plant::~Plant(){}

std::string Plant::getName(){
    return name;
}

int Plant::getMaxWater(){
    return maxWater;
}
void Plant::setMaxWater(int mW){
    this->maxWater = mW;
}
int Plant::getCurrentWater(){
    return currentWater;
}
void Plant::setCurrentWater(int cW){
    this->currentWater = cW;
}

int Plant::getCurrentNutrients(){
    return currentNutrients;
}
void Plant::setCurrentNutrients(int cN){
    this->currentNutrients = cN;
}
int Plant::getMaxNutrients(){
    return maxNurtients;
}
void Plant::setMaxNutrients(int mN){
    this->maxNurtients = mN;
}
int Plant::getCurrentSunlight(){
    return currentSunlight;
}
void Plant::setCurrentSunlight(int sL){
    this->currentSunlight = sL;
}
int Plant::getMaxSunlight(){
    return maxSunlight;
}
void Plant::setMaxSunlight(int mL){
    this->maxSunlight = mL;
}