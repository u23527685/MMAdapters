/**
 *@file Plant.h
 *@brief Abstract base class representing a generic plant
 */

#ifndef PLANT_H
#define PLANT_H

#include <string>

/**
 * @class Plant
 * @brief Abstract interface for all plant types.
 */
class Plant {
public:
    /**
     * @brief Virtual destructor for safe polymorphic destruction.
     */
    virtual ~Plant() = default;

    /**
     * @brief Returns a description of the plant.
     * @return A string describing the plant.
     */
    virtual std::string getDescription() const = 0;

    /**
     * @brief Returns the price of the plant.
     * @return The price as a double.
     */
    virtual double getPrice() const = 0;
};

#endif 
