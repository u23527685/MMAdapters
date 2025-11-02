/**
 *@file BasePLant.h
 *@brief Defines the cincrete implementation of a basic plant.
 */

 #ifndef BASE_PLANT_H
#define BASE_PLANT_H

#include "Plant.h"

/**
 *@class BasePlant
 *@brief Represents a simple, undecorated plant.
 */

class BasePlant : public Plant {
public:
    /**
     *@brief Returns the base description of the plant.
     *@return A string describing the plant.
     */
    std::string getDescription() const override;

    /**
     *@brief Returns the base price of the plant.
     *@return The base price as a double.
     */
    double getPrice() const override;

    
};

#endif
