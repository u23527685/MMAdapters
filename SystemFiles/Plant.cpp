#include "Plant.h"

#include "SeedState.h"
#include "PlantState.h"

Plant::Plant(std::string name) : name(name), currentSunlight(0), currentWater(0), currentNutrients(0),
                                maxNurtients(100), maxWater(100), maxSunlight(100), currentState(nullptr) {
    //currentState = new SeedState(this);
}

Plant::~Plant()
{
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
/**
void Plant::setState(PlantState* state) {
    delete currentState;
    currentState = state;
}

void Plant::request(){
    currentState->handleGrowth(this);
}

std::string Plant::getCurrentState()
{
    return currentState->getState();
}
**/
