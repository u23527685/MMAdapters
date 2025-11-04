/**
 * @file GiftWrap.h
 * @brief Decorator class adding a gift wrapping feature to a Plant.
 *
 * GiftWrap is a concrete decorator extending PlantDecorator. It modifies
 * the description and price of a plant by adding a gift wrap option.
 *
 * @see PlantDecorator
 * @see Plant
 *
 */
#ifndef GIFT_WRAP_H
#define GIFT_WRAP_H

#include "PlantDecorator.h"

/**
 * @class GiftWrap
 * @brief Concrete decorator that adds gift wrapping to a Plant.
 *
 * Enhances the plant's presentation, making it suitable for gifting.
 */
class GiftWrap : public PlantDecorator {
public:
    /**
     * @brief Construct a GiftWrap decorator for the given Plant.
     * @param plant Non-owning pointer to the Plant being decorated.
     */
    GiftWrap(Plant* plant);

    /**
     * @brief Get the plant's description including gift wrap details.
     * @return Enhanced description string.
     */
    std::string getDescription() const override;

    /**
     * @brief Get the plant's price including gift wrap cost.
     * @return Combined price as a double.
     */
    double getPrice() const override;
};

#endif
