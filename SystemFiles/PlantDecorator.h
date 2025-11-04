/**
 * @file PlantDecorator.h
 * @brief Abstract decorator for extending Plant behavior dynamically.
 *
 * This class implements the Decorator pattern, allowing plant objects
 * to be extended with new features (e.g., pots, wrapping) without
 * modifying the original Plant class.
 *
 * @see Plant
 * @see DecorativePot
 * @see GiftWrap
 *
 * @author
 * Rachel Kambala
 */
#ifndef PLANT_DECORATOR_H
#define PLANT_DECORATOR_H

#include "Plant.h"

/**
 * @class PlantDecorator
 * @brief Abstract decorator for dynamically extending Plant behavior.
 */
class PlantDecorator : public Plant {
protected:
    Plant* plant; ///< Pointer to the wrapped Plant object.

public:
    /**
     * @brief Constructs a decorator wrapping the given plant.
     */
    PlantDecorator(Plant* plant);
    virtual ~PlantDecorator();

    /**
     * @brief Get the decorated plant’s description.
     */
    virtual std::string getDescription() const override;

    /**
     * @brief Get the decorated plant’s price.
     */
    virtual double getPrice() const override;
};

#endif 
