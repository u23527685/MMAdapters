/**
 * @file Oak.h
 * @brief Concrete Plant class representing an Oak tree.
 *
 * The Oak class defines a specific type of Plant characterized as an Oak tree.
 * It inherits from the Plant base class and provides descriptive attributes
 * relevant to this plant species.
 *
 * @see Plant
 *
 * @author
 * Mthokozisi Duba
 */
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
