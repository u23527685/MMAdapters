#include "Plant.h"

Plant::Plant(double price, std::string description){
    this->state = nullptr;
    this->waterStrategy = nullptr;
    this->sunlightStrategy = nullptr;
    this->fertilizerStrategy = nullptr;
    this->description = description;
    this->price = price;
    this->name = description;
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

bool Plant::setPrice(double price) {
    this->price = price;
    return true;
}

bool Plant::setDescription(const std::string& description) {
    this->description = description;
    return true;
}

bool Plant::setCategory(const std::string& category) {
    this->category = category;
    return true;
}

std::string Plant::getCategory() const {
    return category;
}

bool Plant::setColor(const std::string& color) {
    this->color = color;
    return true;
}

std::string Plant::getColor() const {
    return color;
}

Plant::Plant(std::string name) {
    this->name = name;

    this->state = nullptr;
    this->waterStrategy = nullptr;
    this->sunlightStrategy = nullptr;
    this->fertilizerStrategy = nullptr;
    this->description = name;
    this->price = price;
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

