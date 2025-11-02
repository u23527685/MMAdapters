/**
 * @file PlantDecorator.h
 * @brief Defines the abstract decorator class for extending plant features.
 */

 #ifndef PLANT_DECORATOR_H
#define PLANT_DECORATOR_H

#include "Plant.h"

/**
 * @class PlantDecorator
 * @brief Abstract decorator class extending Plant functionality dynamically.
 */
class PlantDecorator : public Plant {
protected:
    Plant* plant; ///< Pointer to the plant being decorated.

public:
    /**
     * @brief Constructs a decorator for a specific plant.
     * @param plant Pointer to the plant being decorated.
     */
    PlantDecorator(Plant* plant);

    /**
     * @brief Virtual destructor to safely delete wrapped plant.
     */
    virtual ~PlantDecorator();

    /**
     * @brief Returns the decorated plant’s description.
     * @return A string including the base and added description.
     */
    virtual std::string getDescription() const override;

    /**
     * @brief Returns the decorated plant’s total price.
     * @return A double including the base and additional price.
     */
    virtual double getPrice() const override;
};

#endif 
