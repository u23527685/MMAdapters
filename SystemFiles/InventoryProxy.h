/**
 * @file InventoryProxy.h
 * @brief Proxy class controlling access to plant inventory operations.
 *
 * InventoryProxy provides controlled access to PlantInventory functionality,
 * acting as a protection proxy that can enforce business rules and access control.
 * It coordinates with SalesFloorObserver to maintain consistency between
 * inventory and sales floor displays.
 *
 * @see PlantInventory
 * @see SalesFloorObserver
 *
 */
#ifndef INVENTORYPROXY_H
#define INVENTORYPROXY_H

#include "PlantInventory.h"
#include "SalesFloorObserver.h"
#include <stdexcept>
#include <string>

/**
 * @class InventoryProxy
 * @brief Acts as a proxy to manage plant inventory transactions.
 */
class InventoryProxy {
    PlantInventory* inventory; ///< Pointer to the actual plant inventory being proxied
    SalesFloorObserver* salesObserver; ///< Observer for sales floor display updates
public:
     /**
     * @brief Constructs an InventoryProxy with sales floor observer.
     * @param observer Observer for sales floor updates.
     */
    InventoryProxy(SalesFloorObserver* observer);

    /**
     * @brief Processes plant purchase transaction.
     * @param plant Plant to purchase.
     * @param quantity Number of plants to purchase.
     * @return True if purchase was successful, false otherwise.
     */
    bool buyPlant(Plant* plant, int quantity);
    
    /**
     * @brief Adds stock to inventory.
     * @param plant Plant type to add.
     * @param quantity Number of plants to add.
     */
    void addStock(Plant* plant, int quantity);

    /**
     * @brief Removes stock from inventory.
     * @param plant Plant type to remove.
     * @param quantity Number of plants to remove.
     */
    void removeStock(Plant*, int);

     /**
     * @brief Displays currently available plants.
     * Delegates to the sales floor observer for display.
     */
    void displayAvailablePlants() const {
        if (salesObserver) salesObserver->displayAvailablePlants();
    }
};

#endif
