#ifndef BASE_PLANT_H
#define BASE_PLANT_H

#include "Plant.h"

class BasePlant : public Plant {
public:
    std::string getDescription() const override;
    double getPrice() const override;
};

#endif 
