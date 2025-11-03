#ifndef OAK_H
#define OAK_H
#include "Plant.h"

/**
 * @class Oak
 * @brief Represents an Oak tree plant
 * 
 * This class is a concrete implementation of the Plant class,
 * representing an Oak tree in the plant inventory system.
 */
class Oak : public Plant {
    public:
    /**
     * @brief Constructs an Oak plant object
     * @param price The price of the oak tree
     * @param description A description of the oak tree
     */
    Oak(double price, std::string description) : Plant(price, description) {}
};

#endif
