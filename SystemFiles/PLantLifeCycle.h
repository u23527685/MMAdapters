/**
 * @file PlantLifeCycle.h
 * @brief Represents the life cycle and state transitions of a plant.
 *
 * The PlantLifeCycle class manages plant growth states and applies
 * observer notifications when state changes occur. Implements the
 * State and Observer design patterns.
 *
 * @see PlantState
 * @see LifeCycleObserver
 * @see Plant
 *
 */
#ifndef PLANTLIFECYCLE_H
#define PLANTLIFECYCLE_H
#include "Plant.h"
#include "PlantState.h"
#include <string>
#include <vector>
#include "LifeCycleObserver.h"
#include <memory>
class Plant;
class PlantState;
class LifeCycleObserver;

/**
 * @class PlantLifeCycle
 * @brief Manages the state and observers for a plant’s life cycle.
 */
class PlantLifeCycle{
private:
    std::unique_ptr<PlantState> currentState;
    Plant* p;
    std::vector<LifeCycleObserver*> observers;
    std::string name;
public:
    PlantLifeCycle(Plant* plant, std::unique_ptr<PlantState>initialState, std::string name);
    ~PlantLifeCycle();

    std::string getState();
    PlantState* getStateObj() const;

    //void setState(std::string s);
    void setState(std::unique_ptr<PlantState> state);
    std::unique_ptr<PlantState> releaseState();
    void attach(LifeCycleObserver* ol);
    void detach(LifeCycleObserver* ol);
    void notify();
    void simulateTimePassing();
    bool updatePlant();
    

    Plant* getPlant();
    std::string getName();

    //for unit testing:
    std::vector<LifeCycleObserver*>::iterator observersBegin() { return observers.begin(); }
    std::vector<LifeCycleObserver*>::iterator observersEnd() { return observers.end(); }
};

#endif