#ifndef PLANTLIFECYCLE_H
#define PLANTLIFECYCLE_H
#include "Plant.h"
#include "PlantState.h"
#include <string>
#include <vector>
#include "LifeCycleObserver.h"
class Plant;
class PlantState;
class LifeCycleObserver;

class PlantLifeCycle{
private:
    PlantState* currentState;
    Plant* p;
    std::vector<LifeCycleObserver*> observers;
    std::string name;
    void transitionToCorrectState();
public:
    PlantLifeCycle(Plant* plant, PlantState* initialState, std::string name);
    ~PlantLifeCycle();

    std::string getState();
    PlantState* getStateObj() const;

    //void setState(std::string s);
    void setState(PlantState* state);

    void attach(LifeCycleObserver* ol);
    void detach(LifeCycleObserver* ol);
    void notify();
    void simulateTimePassing();
    bool updatePlant();
    

    Plant* getPlant();
    std::string getName();
};

#endif