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
    std::string category;
    std::string color;

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
    bool setPrice(double price);
    bool setDescription(const std::string& description);
    bool setCategory(const std::string& category);
    std::string getCategory() const;
    bool setColor(const std::string& color);
    std::string getColor() const;
};

#endif
