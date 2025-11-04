/**
 * @file InventoryProxy.h
 * @brief Proxy interface for inventory management operations
 * @author Cobus
 */

#ifndef INVENTORYPROXY_H
#define INVENTORYPROXY_H

#include "PlantInventory.h"
#include "SalesFloorObserver.h"
#include <stdexcept>
#include <string>

/**
 * @class InventoryProxy
 * @brief Proxy class controlling access to plant inventory
 * @details Provides controlled access to inventory operations and notifies observers
 * @author Cobus
 */
class InventoryProxy {
    PlantInventory* inventory;          
    SalesFloorObserver* salesObserver;   

public:
    /**
     * @brief Constructor for InventoryProxy
     * @param observer Pointer to the SalesFloorObserver
     * @return None (constructor)
     * @author Cobus
     */
    InventoryProxy(SalesFloorObserver* observer);

    /**
     * @brief Processes purchase of plants from inventory
     * @param plant Pointer to the Plant to purchase
     * @param quantity Number of plants to purchase
     * @return bool Success status of the purchase
     * @author Cobus
     */
    bool buyPlant(Plant* plant, int quantity);

    /**
     * @brief Adds stock to the inventory
     * @param plant Pointer to the Plant to add
     * @param quantity Number of plants to add
     * @return void
     * @author Cobus
     */
    void addStock(Plant* plant, int quantity);

    /**
     * @brief Removes stock from the inventory
     * @param plant Pointer to the Plant to remove
     * @param quantity Number of plants to remove
     * @return void
     * @author Cobus
     */
    void removeStock(Plant*, int);

    /**
     *  @brief Displays available plants in inventory
     *  @return void
     * @author Cobus
    */
    void displayAvailablePlants() const;
};

#endif