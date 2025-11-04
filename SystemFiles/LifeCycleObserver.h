/**
 * @file LifeCycleObserver.h
 * @brief Observer interface for plant lifecycle state changes
 */

#ifndef LIFECYCLEOBSERVER_H
#define LIFECYCLEOBSERVER_H

#include "PlantLifeCycle.h"

class PlantLifeCycle;

/**
 * @class LifeCycleObserver
 * @brief Abstract observer class for monitoring plant lifecycle changes
 * @details Provides interface for objects that need to be notified of changes
 *          in a plant's lifecycle state
 */
class LifeCycleObserver
{
  public:
    /**
     * @brief Updates the observer with lifecycle changes
     * @param p Pointer to the PlantLifeCycle that changed
     * @return void
     */
    virtual void update(PlantLifeCycle *p);

    /**
     * @brief Virtual destructor
     */
    virtual ~LifeCycleObserver() = default;
};

#endif