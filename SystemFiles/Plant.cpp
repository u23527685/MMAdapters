#include "Plant.h"

Plant::Plant(double price, std::string description) : BasePlant(price, description) {
    this->state = nullptr;
    this->waterStrategy = nullptr;
    this->sunlightStrategy = nullptr;
    this->fertilizerStrategy = nullptr;
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

// Detaches an observer from the plant
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
