#include "Plant.h"

Plant::Plant(double price, std::string description){
    this->state = nullptr;
    this->waterStrategy = nullptr;
    this->sunlightStrategy = nullptr;
    this->fertilizerStrategy = nullptr;
    this->description = description;
    this->price = price;
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
