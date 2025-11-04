/**
 * @file SpecialArrangement.h
 * @brief Decorator for plants that adds a special arrangement feature.
 *
 * The SpecialArrangement class is a PlantDecorator that modifies
 * the plant description and price to reflect special arrangements.
 *
 * @see PlantDecorator
 * @see Plant
 *
 */
#ifndef SPECIAL_ARRANGEMENT_H
#define SPECIAL_ARRANGEMENT_H

#include "PlantDecorator.h"

/**
 * @class SpecialArrangement
 * @brief Concrete decorator that adds a special arrangement to a plant.
 */
class SpecialArrangement : public PlantDecorator {
public:
    SpecialArrangement(Plant* plant);
    std::string getDescription() const override;
    double getPrice() const override;
};

#endif 
