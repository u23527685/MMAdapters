#ifndef PLANT_H
#define PLANT_H
#include <string>
#include <vector>
#include "BasePlant.h"
class WateringStrategy;
class SunlightStrategy;
class FertilizerStrategy;
class PlantState;
class LifeCycleObserver;

class Plant: public BasePlant {
public:
protected:
    WateringStrategy* waterStrategy;
    SunlightStrategy* sunlightStrategy;
    FertilizerStrategy* fertilizerStrategy;
    PlantState* state;
    std::vector<LifeCycleObserver*> observerList;

public:
    Plant(double price, std::string description);
    void applyCare();
    void setState(PlantState* s);
    PlantState* getState();
    void attach(LifeCycleObserver* o);
    void detach(LifeCycleObserver* o);
    void notify();
};

#endif
