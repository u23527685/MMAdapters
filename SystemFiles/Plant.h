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
#include <memory>

/**
 * @class Plant
 * @brief Abstract base class representing a plant in the inventory system
 * 
 * This class manages plant properties including watering, sunlight, nutrients,
 * growth state, and lifecycle observers. It supports the Observer pattern for
 * lifecycle events and State pattern for growth stages.
 */
class Plant {
private:
    std::string name;
    

    int currentSunlight;
    int currentWater;
    int currentNutrients;

    int maxNutrtients =200;
    int maxWater=200;
    int maxSunlight=200;

    int minWater = 10;
    int minSunlight = 10;
    int minNutrients = 10;

    int growthProgress = 0;

    std::unique_ptr<PlantState> state;
protected:
    WateringStrategy* waterStrategy;
    SunlightStrategy* sunlightStrategy;
    FertilizerStrategy* fertilizerStrategy;
    std::vector<LifeCycleObserver*> observerList;
    std::string category;
    std::string description;
    double price;
    std::string color;

public:
    /**
     * @brief Default constructor
     */
    Plant();
    
    /**
     * @brief Parameterized constructor
     * @param price The price of the plant
     * @param description Description of the plant
     */
    Plant(double price, std::string description);

    /**
     * @brief Applies care routines to the plant
     */
    void applyCare();
    
    /**
     * @brief Sets the state of the plant
     * @param s New state to set
     */
    void setState(std::unique_ptr<PlantState> s){state = std::move(s);}
    
    /**
     * @brief Gets the current state of the plant
     * @return Pointer to the current PlantState
     */
    PlantState* getState(){return state.get();}
    
    /**
     * @brief Attaches a lifecycle observer to the plant
     * @param o Observer to attach
     */
    void attach(LifeCycleObserver* o);
    
    /**
     * @brief Detaches a lifecycle observer from the plant
     * @param o Observer to detach
     */
    void detach(LifeCycleObserver* o);
    
    /**
     * @brief Notifies all attached observers of changes
     */
    void notify();
    
    /**
     * @brief Gets the plant description
     * @return Description string
     */
    virtual std::string getDescription() const;
    
    /**
     * @brief Gets the plant price
     * @return Price value
     */
    virtual double getPrice() const;
    
    /**
     * @brief Sets the color of the plant
     * @param color Color to set
     * @return true if successful
     */
    bool setColor(const std::string& color);
    
    /**
     * @brief Gets the plant color
     * @return Color string
     */
    std::string getColor() const;

    /**
     * @brief Gets the plant name
     * @return Name string
     */
    std::string getName();
    
    /**
     * @brief Gets the maximum water capacity
     * @return Maximum water value
     */
    int getMaxWater();
    
    /**
     * @brief Sets the maximum water capacity
     * @param mW Maximum water value
     */
    void setMaxWater(int mW);
    
    /**
     * @brief Gets the current water level
     * @return Current water value
     */
    int getCurrentWater();
    
    /**
     * @brief Sets the current water level
     * @param cW Current water value (capped at max)
     */
    void setCurrentWater(int cW);
    
    /**
     * @brief Gets the current nutrient level
     * @return Current nutrient value
     */
    int getCurrentNutrients();
    
    /**
     * @brief Sets the current nutrient level
     * @param cN Current nutrient value (capped at max)
     */
    void setCurrentNutrients(int cN);
    
    /**
     * @brief Gets the maximum nutrient capacity
     * @return Maximum nutrient value
     */
    int getMaxNutrients();
    
    /**
     * @brief Sets the maximum nutrient capacity
     * @param mN Maximum nutrient value
     */
    void setMaxNutrients(int mN);
    
    /**
     * @brief Gets the current sunlight level
     * @return Current sunlight value
     */
    int getCurrentSunlight();
    
    /**
     * @brief Sets the current sunlight level
     * @param mL Current sunlight value (capped at max)
     */
    void setCurrentSunlight(int mL);
    
    /**
     * @brief Gets the maximum sunlight capacity
     * @return Maximum sunlight value
     */
    int getMaxSunlight();
    
    /**
     * @brief Sets the maximum sunlight capacity
     * @param mL Maximum sunlight value
     */
    void setMaxSunlight(int mL);
    
    /**
     * @brief Gets the minimum water requirement
     * @return Minimum water value
     */
    int getMinWater() const ;
    
    /**
     * @brief Gets the minimum sunlight requirement
     * @return Minimum sunlight value
     */
    int getMinSunlight() const ;
    
    /**
     * @brief Gets the minimum nutrient requirement
     * @return Minimum nutrient value
     */
    int getMinNutrients() const;
    
    /**
     * @brief Gets the plant category
     * @return Category string
     */
    std::string getCategory();
    
    /**
     * @brief Sets the plant category
     * @param c Category string
     */
    void setCategory( const std::string& c);

    /**
     * @brief Gets the current growth progress
     * @return Growth progress value
     */
    int getGrowthProgress() const;
    
    /**
     * @brief Sets the growth progress
     * @param gp Growth progress value
     */
    void setGrowthProgress(int gp);
    
    /**
     * @brief Increments the growth progress by 1
     */
    void increaseGrowthProgress();

    virtual ~Plant();
};

#endif
