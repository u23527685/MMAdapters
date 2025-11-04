/**
 * @file PlantDecorator.h
 * @brief Header file for the PlantDecorator class
 */

#ifndef PLANT_DECORATOR_H
#define PLANT_DECORATOR_H

#include "Plant.h"

/**
 * @class PlantDecorator
 * @brief Base decorator class for adding features to plants
 * @details Implements the decorator pattern to allow dynamic addition of
 *          features and modifications to plant objects
 */
class PlantDecorator : public Plant
{
  protected:
    Plant *plant; ///< Pointer to the decorated plant object

  public:
    /**
     * @brief Constructor for PlantDecorator
     * @param plant Pointer to the Plant object to be decorated
     * @return None (constructor)
     */
    PlantDecorator(Plant *plant);
    PlantDecorator(Plant *plant);

    /**
     * @brief Virtual destructor for PlantDecorator
     * @return None (destructor)
     */
    virtual ~PlantDecorator();

    /**
     * @brief Gets the description of the decorated plant
     * @return std::string The description including decoration details
     */
    virtual std::string getDescription() const override;

    /**
     * @brief Gets the total price of the decorated plant
     * @return double The price including decoration costs
     */
    virtual double getPrice() const override;
};

<<<<<<< HEAD
#endif
=======
#endif
