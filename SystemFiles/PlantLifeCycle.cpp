#include "PlantLifeCycle.h"
#include "DistressedState.h"
#include "WitheredState.h"
#include <memory>

PlantLifeCycle::PlantLifeCycle(Plant *plant,
                               std::unique_ptr<PlantState> initialState,
                               std::string name)
    : p(plant), currentState(std::move(initialState)), name(name)
{
}

PlantLifeCycle::~PlantLifeCycle() {}

std::string PlantLifeCycle::getState()
{
    return currentState ? currentState->getName() : "Unknown";
}

// Return a raw pointer temporarily for external access
PlantState *PlantLifeCycle::getStateObj() const { return currentState.get(); }

void PlantLifeCycle::setState(std::unique_ptr<PlantState> state)
{
    if (state)
    {
        currentState = std::move(state);
        notify();
    }
}

std::unique_ptr<PlantState> PlantLifeCycle::releaseState()
{
    return std::move(currentState);
}

void PlantLifeCycle::attach(LifeCycleObserver *obs)
{
    observers.push_back(obs);
}

void PlantLifeCycle::detach(LifeCycleObserver *obs)
{
    for (auto it = observers.begin(); it != observers.end(); ++it)
    {
        if (*it == obs)
        {
            observers.erase(it);
            break;
        }
    }
}

void PlantLifeCycle::notify()
{
    for (auto obs : observers)
    {
        obs->update(this);
    }
}

bool PlantLifeCycle::updatePlant()
{
    return currentState->evaluate(this, p); // delegate to state
}

void PlantLifeCycle::simulateTimePassing()
{
    Plant *plant = getPlant();
    if (plant->getCategory() != "Shade")
    {
        plant->setCurrentSunlight(plant->getCurrentSunlight() - 10);
    }
    else
    {
        plant->setCurrentSunlight(0);
    }
    plant->setCurrentWater(plant->getCurrentWater() - 10);
    plant->setCurrentNutrients(plant->getCurrentNutrients() - 10);
}

Plant *PlantLifeCycle::getPlant() { return p; }

std::string PlantLifeCycle::getName() { return name; }
