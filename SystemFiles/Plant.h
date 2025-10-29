#ifndef PLANT_H
#define PLANT_H
#include <string>
#include <vector>
#include <utility>

#include "PlantState.h"
#include "WateringStrategy.h"
#include "SunlightStrategy.h"
#include "FertilizerStrategy.h"
#include "LifeCycleObserver.h"

class WateringStrategy;
class SunlightStrategy;
class FertilizerStrategy;
class PlantState;
class LifeCycleObserver;

class Plant {
public:
  
 //TK's code
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

 //Isha's code
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

    PlantState* currentState;  // State context
public:
    Plant(std::string name);
    virtual ~Plant();
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

};
#endif
