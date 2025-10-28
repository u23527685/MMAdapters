#ifndef PLANT_H
#define PLANT_H

#include <string>

class Plant{
private:
    std::string name;

    int currentSunlight;
    int currentWater;
    int currentNutrients;

    int maxNurtrients;
    int maxWater;
    int maxSunlight;

    int minWater;
    int minSunlight;
    int minNutrients;

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