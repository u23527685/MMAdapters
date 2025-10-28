#include "Plant.h"

Plant::Plant(double price, std::string description)
    : name(description),
      description(description), 
      price(price),
      currentState(nullptr),
      waterStrategy(nullptr),
      sunlightStrategy(nullptr),
      fertilizerStrategy(nullptr),
      state(nullptr),
      currentSunlight(0),
      currentWater(0),
      currentNutrients(0),
      maxNutrtients(100),
      maxWater(100),
      maxSunlight(100),
      minWater(0),
      minSunlight(0),
      minNutrients(0)
{
}

// Applies care routines
void Plant::applyCare() {
    
}

void Plant::setState(PlantState* s) {
    state = s;
}

PlantState* Plant::getState() {
    return state;
}

// Attaches an observer to the plant
void Plant::attach(LifeCycleObserver* o) {
    observerList.push_back(o);
}

// Detaches an observer to the Plant
void Plant::detach(LifeCycleObserver* o) {
    for (std::vector<LifeCycleObserver*>::iterator it = observerList.begin(); it != observerList.end(); ++it) {
        if (*it == o) {
            observerList.erase(it);
            break;
        }
    }
}


void Plant::notify() {

}

std::string Plant::getDescription() {
    return description;
}

double Plant::getPrice() {
    return price;
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
