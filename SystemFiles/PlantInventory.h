/**
 * @file PlantInventory.h
 * @brief Manages plant inventory using Singleton and Observer patterns.
 *
 * The PlantInventory class maintains a record of all plants in stock.
 * It supports attaching observers and executing commands that modify
 * stock quantities. Implements the Singleton pattern for shared access.
 *
 * @see InventoryObserver
 * @see PlantStock
 * @see StockCommand
 *
 */
#ifndef PLANTINVENTORY_H
#define PLANTINVENTORY_H
#include <vector>
#include <string>
#include <algorithm>
#include "InventoryObserver.h"
#include "Plant.h"
#include "StockCommand.h"

/**
 * @class PlantInventory
 * @brief Singleton class managing plant inventory and observers.
 */
class PlantInventory {
private:
    static PlantInventory* instance;
    std::vector<InventoryObserver*> inventoryObservers;
    std::vector<std::pair<Plant*, int>> inventoryItems;

    /**
     * @brief Private constructor for singleton pattern
     */
    PlantInventory();

public:
    /**
     * @brief Gets the singleton instance of PlantInventory
     * @return Pointer to the singleton instance
     */
    static PlantInventory* getInstance();

    ~PlantInventory();

    /**
     * @brief Attaches an observer to the inventory
     * @param observer Observer to attach
     * @return true if successful
     */
    bool attach(InventoryObserver* observer);
    
    /**
     * @brief Detaches an observer from the inventory
     * @param observer Observer to detach
     * @return true if successful
     */
    bool detach(InventoryObserver* observer);
    
    /**
     * @brief Notifies all observers if changes are made
     */
    void notify();
    
    /**
     * @brief Updates stock and notifies observers
     */
    void updateStock();

    /**
     * @brief Adds stock to inventory (creates and executes AddStock command)
     * @param plant Plant to add
     * @param quantity Quantity to add
     * @return true if successful
     */
    bool addStock(Plant* plant, int quantity);
    
    /**
     * @brief Removes stock from inventory (creates and executes RemoveStock command)
     * @param plant Plant to remove
     * @param quantity Quantity to remove
     * @return true if successful
     */
    bool removeStock(Plant* plant, int quantity);
    
    /**
     * @brief Executes a stock command and removes it from memory
     * @param command Command to execute
     * @return true if execution successful
     */
    bool executeCommand(StockCommand* command);

    /**
     * @brief Gets a reference to inventory items for command operations
     * @return Reference to inventory vector
     */
    std::vector<std::pair<Plant*, int>>& getInventoryReference();

    /**
     * @brief Gets a copy (not reference) of inventory
     * @return Copy of inventory vector
     */
    const std::vector<std::pair<Plant*, int>> getInventoryView() const;

    /**
     * @brief Finds inventory index for a given Plant
     * @param plant Plant to find
     * @return Index of plant in inventory, or -1 if not found
     */
    int findPlantIndex(Plant* plant) const;

    /**
     * @brief Gets the quantity of a specific plant in inventory
     * @param plant Plant to query
     * @return Quantity of the plant, or 0 if not found
     */
    int getQuantity(Plant* plant) const;

};

#endif
