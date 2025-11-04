/**
 * @file PlantLifeCycle.h
 * @brief Header file for the PlantLifeCycle class
 */

#ifndef PLANTLIFECYCLE_H
#define PLANTLIFECYCLE_H
#include "Plant.h"
#include "PlantState.h"
#include <memory>
#include <string>
#include <vector>
#include "LifeCycleObserver.h"
#include <memory>

class Plant;
class PlantState;
class LifeCycleObserver;

/**
 * @class PlantLifeCycle
 * @brief Manages the life cycle states and transitions of a plant
 * @details Controls state transitions, observer notifications, and plant updates 
 *          throughout its growth cycle
 */
class PlantLifeCycle {
private:
    std::unique_ptr<PlantState> currentState;    ///< Current state of the plant
    Plant* p;                                    ///< Pointer to the associated plant
    std::vector<LifeCycleObserver*> observers;   ///< List of lifecycle observers
    std::string name;                           ///< Name of the lifecycle

public:
    /**
     * @brief Constructor for PlantLifeCycle
     * @param plant Pointer to the Plant object
     * @param initialState Initial state of the plant
     * @param name Name of the lifecycle
     */
    PlantLifeCycle(Plant* plant, std::unique_ptr<PlantState>initialState, std::string name);

    /**
     * @brief Destructor for PlantLifeCycle
     */
    ~PlantLifeCycle();

    /**
     * @brief Gets the current state name
     * @return std::string Name of the current state
     */
    std::string getState();

    /**
     * @brief Gets the current state object
     * @return PlantState* Pointer to the current state object
     */
    PlantState* getStateObj() const;

    /**
     * @brief Sets a new state for the plant
     * @param state New state to set
     * @return void
     */
    void setState(std::unique_ptr<PlantState> state);

    /**
     * @brief Releases ownership of current state
     * @return std::unique_ptr<PlantState> The released state object
     */
    std::unique_ptr<PlantState> releaseState();

    /**
     * @brief Attaches an observer to the lifecycle
     * @param ol Pointer to the observer to attach
     * @return void
     */
    void attach(LifeCycleObserver* ol);

    /**
     * @brief Detaches an observer from the lifecycle
     * @param ol Pointer to the observer to detach
     * @return void
     */
    void detach(LifeCycleObserver* ol);

    /**
     * @brief Notifies all observers of state changes
     * @return void
     */
    void notify();

    /**
     * @brief Simulates the passage of time for the plant
     * @return void
     */
    void simulateTimePassing();

    /**
     * @brief Updates the plant's state based on current conditions
     * @return bool Success status of the update
     */
    bool updatePlant();

    /**
     * @brief Gets the associated plant object
     * @return Plant* Pointer to the plant
     */
    Plant* getPlant();

    /**
     * @brief Gets the lifecycle name
     * @return std::string The name of the lifecycle
     */
    std::string getName();

    /**
     * @brief Gets iterator to beginning of observers list
     * @return std::vector<LifeCycleObserver*>::iterator Iterator to first observer
     */
    std::vector<LifeCycleObserver*>::iterator observersBegin() { return observers.begin(); }

    /**
     * @brief Gets iterator to end of observers list
     * @return std::vector<LifeCycleObserver*>::iterator Iterator past last observer
     */
    std::vector<LifeCycleObserver*>::iterator observersEnd() { return observers.end(); }
};

#endif