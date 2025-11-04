/**
 * @file Rose.h
 * @brief Defines a concrete Rose plant class.
 *
 * The Rose class represents a type of plant with a specified
 * price and description. It inherits from the Plant base class.
 *
 * @see Plant
 *
 */
#ifndef ROSE_H
#define ROSE_H
#include "Plant.h"

/**
 * @class Rose
 * @brief Concrete implementation of the Plant class for roses.
 */
class Rose : public Plant {
    protected:
    double price; ///< Price of the rose.
    std::string description; ///< Description of the rose.
    public:
    /**
     * @brief Constructs a Rose plant
     * @param price The price of the rose
     * @param description A description of the rose
     */
    Rose(double price, std::string description) : Plant(price, description) {}
};

#endif 
