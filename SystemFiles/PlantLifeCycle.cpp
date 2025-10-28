#include "PLantLifeCycle.h"

PlantLifeCycle::PlantLifeCycle(Plant* plant, PlantState* initialState, std::string name)
    :  p(plant), currentState(initialState), name(name)
{
}

PlantLifeCycle::~PlantLifeCycle() {
    delete currentState;
}

std::string PlantLifeCycle::getState(){
    return name;
}

PlantState* PlantLifeCycle::getStateObj() const {
    return currentState;
}

/**
void PlantLifeCycle::setState(std::string s){
    this->state = s;
} **/

void PlantLifeCycle::setState(PlantState* state) {
    if (currentState->getName() != state->getName()) {
        delete currentState;
        currentState = state;
        notify(); // only notify if state actually changed
    }
}
/**
void PlantLifeCycle::attach(LifeCycleObserver* obs){
    observers.push_back(obs);
}

void PlantLifeCycle::detach(LifeCycleObserver* obs){
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == obs) {
            observers.erase(it);
            break; 
        }
    }
}
**/
void PlantLifeCycle::notify() {
        for (auto obs : observers) {
            obs->update(this);
        }
}

bool PlantLifeCycle::isHealthy(){
    return currentState->evaluate(this, p); //delegate to state
}

/**

bool PlantLifeCycle::isHealthy(){
    if(p->getCurrentWater() < 20 || p->getCurrentSunlight() < 20 || p->getCurrentNutrients() < 20){
        p->setState("Distressed");
        return false;
    } else if(p->getCurrentWater() < 10 || p->getCurrentSunlight() < 10 || p->getCurrentNutrients() < 10){
        p->setState("Withered");
        return false;
    } else if(p->getCurrentWater() >= 20 && p->getCurrentSunlight() >= 20 && p->getCurrentNutrients() >= 20){
        return true;
    }
    else if(p->getCurrentWater() >= 40 && p->getCurrentSunlight() >= 40 && p->getCurrentNutrients() >= 40){
        p->setState("Seedling");
        return true;
    }
    else{
        p->setState("Mature");
        return true;
    }
}

**/

Plant* PlantLifeCycle::getPlant() {
    return p;
}

std::string PlantLifeCycle::getName() {
    return name;
}