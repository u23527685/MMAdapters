#ifndef PLANT_H
#define PLANT_H

#include <string>

class Plant{
private:
    std::string name;
    int currentSunlight;
    int currentWater;
    int currentNutrients;
    int maxNurtients;
    int maxWater;
    int maxSunlight;
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
};
#endif