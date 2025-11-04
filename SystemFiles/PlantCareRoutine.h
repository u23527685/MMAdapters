/**
 * @file PlantCareRoutine.h
 * @brief Header file for the PlantCareRoutine class
 */

#ifndef PLANTCAREROUTINE_H
#define PLANTCAREROUTINE_H

#include "Plant.h"
#include <iostream>
#include <memory>

class Plant;

/**
 * @class PlantCareRoutine
 * @brief Abstract base class defining interface for plant care routines
 * @details Provides a framework for implementing different plant care
 * strategies
 */
class PlantCareRoutine
{
  public:
    /**
     * @brief Virtual destructor
     */
    virtual ~PlantCareRoutine() = default;

    /**
     * @brief Factory method to create appropriate care routine for a plant
     * @param p Pointer to the Plant object needing care
     * @return std::unique_ptr<PlantCareRoutine> Smart pointer to created care
     * routine
     */
    static std::unique_ptr<PlantCareRoutine> PlantCare(Plant *p);

    /**
     * @brief Pure virtual function for fertilizing a plant
     * @param p Pointer to the Plant object to be fertilized
     * @return void
     */
    virtual void Fertilizing(Plant *p) = 0;

    /**
     * @brief Pure virtual function for watering a plant
     * @param p Pointer to the Plant object to be watered
     * @return void
     */
    virtual void Watering(Plant *p) = 0;

    /**
     * @brief Pure virtual function for managing plant sunlight
     * @param p Pointer to the Plant object needing sunlight management
     * @return void
     */
    virtual void Sunlight(Plant *p) = 0;

    /**
     * @brief Pure virtual function for printing care routine details
     * @return void
     */
    virtual void printCareRoutine() = 0;
};

#endif