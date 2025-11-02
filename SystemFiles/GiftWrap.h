/**
 * @file GiftWrap.h
 * @brief Concrete decorator for adding gift wrapping to a plant.
 */
 
#ifndef GIFT_WRAP_H
#define GIFT_WRAP_H

#include "PlantDecorator.h"

/**
 * @class GiftWrap
 * @brief Adds gift wrapping to a plant.
 */
class GiftWrap : public PlantDecorator {
public:
     /**
     * @brief Constructs a GiftWrap decorator.
     * @param plant Pointer to the plant being decorated.
     */
    GiftWrap(Plant* plant);

    /**
     * @brief Returns the plant description with gift wrapping details.
     * @return A string describing the decorated plant.
     */
    std::string getDescription() const override;

    /**
     * @brief Returns the total price including gift wrapping.
     * @return The updated price as a double.
     */
    double getPrice() const override;
};

#endif
