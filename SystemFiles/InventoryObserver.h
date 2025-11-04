/**
 * @file InventoryObserver.h
 * @brief Abstract base class for observers monitoring plant inventory changes.
 *
 * InventoryObserver defines the interface for objects that need to be notified
 * when changes occur in the plant inventory. Concrete observers must implement
 * the update method to respond to inventory changes.
 *
 * @see PlantInventory
 *
 * @author
 * Mthokozisi Duba
 */
#ifndef INVENTORYOBSERVER_H
#define INVENTORYOBSERVER_H

#include "Plant.h"

class PlantInventory;

/**
 * @class InventoryObserver
 * @brief Abstract base class for observers of inventory changes
 * 
 * This class implements the Observer, allowing objects
 * to be notified when the plant inventory changes.
 */
class InventoryObserver {
protected:
    PlantInventory* inventory; ///< Pointer to the observed plant inventory
public:
    /**
     * @brief Constructs an observer and attaches to inventory
     * @param inventory Inventory to observe
     */
    InventoryObserver(PlantInventory* inventory);
    
    virtual ~InventoryObserver();
    
    /**
     * @brief Pure virtual method called when inventory changes
     */
    virtual void update() = 0;
};

#endif
