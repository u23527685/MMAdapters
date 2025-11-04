/**
 * @file LifeCycleObserver.h
 * @brief Abstract base class for observers monitoring plant life cycle changes.
 *
 * LifeCycleObserver defines the interface for objects that need to be notified
 * when changes occur in a plant's life cycle. Observers can track growth stages,
 * health changes, and other life cycle events.
 *
 * @see PlantLifeCycle
 *
 * @author
 * Jay Lopes
 */
#ifndef LIFECYCLEOBSERVER_H
#define LIFECYCLEOBSERVER_H

#include "PlantLifeCycle.h"

class PlantLifeCycle;

/**
 * @class LifeCycleObserver
 * @brief Observer interface for plant life cycle changes.
 *
 * Implement this interface to receive notifications when a plant's
 * life cycle state changes.
 */
class LifeCycleObserver{
    public:
    /**
     * @brief Called when the observed plant's life cycle changes.
     * @param p Pointer to the PlantLifeCycle that changed.
     */
    virtual void update(PlantLifeCycle* p);

    /**
     * @brief Virtual destructor for proper cleanup.
     */
    virtual ~LifeCycleObserver() = default;
};

#endif