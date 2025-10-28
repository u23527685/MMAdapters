#include "Plant.h"
#include "PlantState.h"

Plant::Plant(std::string name) {
    this->name = name;
}
Plant::~Plant(){
    delete currentState;
}
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
    if (cW > maxWater) {
        this->currentWater = maxWater;
    } else {
        this->currentWater = cW;
    }
}
int Plant::getCurrentNutrients(){
    return currentNutrients;
}
void Plant::setCurrentNutrients(int cN){
    if (cN > maxNutrtients) {
        this->currentNutrients = maxNutrtients;
    } else {
        this->currentNutrients = cN;
    }
}
int Plant::getMaxNutrients(){
    return maxNutrtients;
}
void Plant::setMaxNutrients(int mN){
    this->maxNutrtients = mN;
}
int Plant::getCurrentSunlight(){
    return currentSunlight;
}
void Plant::setCurrentSunlight(int sL){
    if (sL > maxSunlight) {
        this->currentSunlight = maxSunlight;
    } else {
        this->currentSunlight = sL;
    }
}
int Plant::getMaxSunlight(){
    return maxSunlight;
}
void Plant::setMaxSunlight(int mL){
    this->maxSunlight = mL;
}
int Plant::getMinWater() const{
    return minWater;
}
int Plant::getMinSunlight() const{
    return minSunlight;
}
int Plant::getMinNutrients() const{
    return minNutrients;
}

