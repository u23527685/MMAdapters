/**
 * @file GiftWrap.h
 * @brief Header file for the GiftWrap decorator class
 */

#ifndef GIFT_WRAP_H
#define GIFT_WRAP_H

#include "PlantDecorator.h"

/**
 * @class GiftWrap
 * @brief Decorator class for adding gift wrapping to plants
 * @details Provides functionality to wrap plants as gifts and adjust pricing
 * accordingly
 */
class GiftWrap : public PlantDecorator
{
  public:
    /**
     * @brief Constructor for GiftWrap decorator
     * @param plant Pointer to the Plant object to be gift wrapped
     * @return None (constructor)
     */
    GiftWrap(Plant *plant);

    /**
     * @brief Gets the description of the gift wrapped plant
     * @return std::string The description including gift wrap details
     */
    std::string getDescription() const override;

    /**
     * @brief Gets the total price including gift wrapping
     * @return double The price including gift wrap cost
     */
    double getPrice() const override;
};

#endif