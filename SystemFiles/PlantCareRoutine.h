/**
 * @file PlantCareRoutine.h
 * @brief Defines the abstract interface for plant care routines.
 *
 * The PlantCareRoutine class provides a template for applying care
 * operations (watering, fertilizing, and sunlight exposure) to plants.
 * It supports dynamic creation of specific care routines.
 *
 * @see Plant
 * @see PlantLifeCycle
 *
 */
#ifndef PLANTCAREROUTINE_H
#define PLANTCAREROUTINE_H

#include <string>
#include "Plant.h"
#include <iostream>
#include <memory>


class Plant;

/**
 * @class PlantCareRoutine
 * @brief Abstract base class defining a plant care routine interface.
 */
class PlantCareRoutine{
public:
    virtual ~PlantCareRoutine() = default;

     /**
     * @brief Factory method for creating care routines.
     * @param p Pointer to the plant needing care.
     * @return Unique pointer to a new PlantCareRoutine instance.
     */
    static std::unique_ptr<PlantCareRoutine> PlantCare(Plant* p);

    /**
     * @brief Apply fertilization routine to a plant.
     */
    virtual void Fertilizing(Plant* p) = 0;

    /**
     * @brief Apply watering routine to a plant.
     */
    virtual void Watering(Plant* p) =0;

    /**
     * @brief Apply sunlight exposure routine to a plant.
     */
    virtual void Sunlight(Plant* p)= 0;

     /**
     * @brief Print the details of the care routine.
     */
    virtual void printCareRoutine() = 0;
};

#endif