#ifndef PLANT_H
#define PLANT_H
#include <string>
#include <vector>
#include <utility>
class WateringStrategy;
class SunlightStrategy;
class FertilizerStrategy;
class PlantState;
class LifeCycleObserver;

class Plant {
public:
protected:
    WateringStrategy* waterStrategy;
    SunlightStrategy* sunlightStrategy;
    FertilizerStrategy* fertilizerStrategy;
    PlantState* state;
    std::vector<LifeCycleObserver*> observerList;

    std::string description;
    double price;

public:
    Plant(double price, std::string description);
    void applyCare();
    void setState(PlantState* s);
    PlantState* getState();
    void attach(LifeCycleObserver* o);
    void detach(LifeCycleObserver* o);
    void notify();
    std::string getDescription();
    double getPrice();
};

#endif
