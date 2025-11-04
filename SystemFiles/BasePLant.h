/**
 * @file BasePlant.h
 * @brief Concrete implementation of a basic Plant type.
 *
 * BasePlant represents a generic plant with a price and a textual description.
 * It provides default implementations for retrieving these details.
 */
#ifndef BASEPLANT_H
#define BASEPLANT_H
#include <string>
#include "Plant.h"

/**
 * @class BasePlant
 * @brief Represents a basic plant with a price and description.
 *
 * This class extends the Plant base class and provides concrete
 * implementations for retrieving plant price and description.
 */
class BasePlant: public Plant {
    public:
    /**
     * @brief Default constructor for BasePlant.
     */
    BasePlant();

    /**
     * @brief Parameterized constructor to initialize a BasePlant.
     * @param p The price of the plant.
     * @param desc The description of the plant.
     */
    BasePlant(double p, std::string desc);

    /**
     * @brief Virtual destructor for BasePlant.
     */
    virtual ~BasePlant() {}

    /**
     * @brief Retrieves the plant's description.
     * @return A string describing the plant.
     */
    std::string getDescription() const override;

    /**
     * @brief Retrieves the plant's price.
     * @return The price of the plant as a double.
     */
    double getPrice() const override;
};

#endif
