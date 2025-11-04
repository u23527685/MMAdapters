#ifndef ROSE_H
#define ROSE_H
#include "Plant.h"

/**
 * @class Rose
 * @brief Represents a Rose flower plant
 *
 * This class is a concrete implementation of the Plant class,
 * representing a Rose flower in the plant inventory system.
 */
class Rose : public Plant
{
  protected:
    double price;
    std::string description;

  public:
    /**
     * @brief Constructs a Rose plant
     * @param price The price of the rose
     * @param description A description of the rose
     */
    Rose(double price, std::string description) : Plant(price, description) {}
};

#endif
