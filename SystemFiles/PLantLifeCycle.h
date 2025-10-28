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
public:
    PlantLifeCycle(Plant* plant, PlantState* initialState, std::string name);
    ~PlantLifeCycle();

    std::string getState();
    PlantState* getStateObj() const;

    //void setState(std::string s);
    void setState(PlantState* state);

    void attach(PlantState* ol);
    void detach(PlantState* ol);
    void notify();
    bool isHealthy();

    Plant* getPlant();
    std::string getName();
};

#endif