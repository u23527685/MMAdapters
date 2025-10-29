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
