/**
 * @file BasePlant.h
 * @brief Defines the BasePlant class, a concrete implementation of the Plant interface.
 */

#ifndef BASEPLANT_H
#define BASEPLANT_H
#include <string>
#include "Plant.h"

/**
 * @class BasePlant
 * @brief Represents a basic plant with a description and price.
 */
class BasePlant: public Plant {
    public:
    /**
     * @brief Default constructor for BasePlant.
     */
    BasePlant();

    /**
     * @brief Constructs a BasePlant with a specified price and description.
     * @param p The price of the plant.
     * @param desc The description of the plant.
     */
    BasePlant(double p, std::string desc);

    /**
     * @brief Virtual destructor for BasePlant.
     */
    virtual ~BasePlant() {}

    /**
     * @brief Retrieves the description of the plant.
     * @return A string containing the plant description.
     */
    std::string getDescription() const override;

    /**
     * @brief Retrieves the price of the plant.
     * @return The price of the plant.
     */
    double getPrice() const override;
};

#endif
