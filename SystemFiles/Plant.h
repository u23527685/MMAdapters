#ifndef PLANT_H
#define PLANT_H

#include "PlantState.h"

class WateringStrategy;
class SunlightStrategy;
class FertilizerStrategy;
class PlantState;
class LifeCycleObserver;
class PlantState;

#include <string>
#include <vector>
#include <utility>

class Plant {
private:
    std::string name;
    

    int currentSunlight;
    int currentWater;
    int currentNutrients;

    int maxNutrtients;
    int maxWater;
    int maxSunlight;

    int minWater;
    int minSunlight;
    int minNutrients;

    PlantState* currentState;
protected:
    WateringStrategy* waterStrategy;
    SunlightStrategy* sunlightStrategy;
    FertilizerStrategy* fertilizerStrategy;
    PlantState* state;
    std::vector<LifeCycleObserver*> observerList;
    std::string category;

    std::string description;
    double price;
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
    bool setColor(const std::string& color);
    std::string getColor() const;

    std::string getName();
    int getMaxWater();
    void setMaxWater(int mW);
    int getCurrentWater();
    void setCurrentWater(int cW);
    int getCurrentNutrients();
    void setCurrentNutrients(int cN);
    int getMaxNutrients();
    void setMaxNutrients(int mN);
    int getCurrentSunlight();
    void setCurrentSunlight(int mL);
    int getMaxSunlight();
    void setMaxSunlight(int mL);
    int getMinWater() const ;
    int getMinSunlight() const ;
    int getMinNutrients() const;
    std::string getCategory();
    void setCategory( const std::string& c);

    virtual ~Plant();
};

#endif
