#ifndef PLANTINVENTORY_H
#define PLANTINVENTORY_H
#include <vector>
#include <string>
#include <algorithm>
#include "InventoryObserver.h"
#include "Plant.h"
#include "StockCommand.h"

// PlantInventory acts as the Receiver in the Command pattern from StockCommand
class PlantInventory {
private:
    // List of observers
    std::vector<InventoryObserver*> inventoryObservers;
    // Inventory which contains a pair of Plant pointer and its quantity
    std::vector<std::pair<Plant*, int>> inventoryItems;

public:
    PlantInventory();
    ~PlantInventory();

    bool attach(InventoryObserver* observer);
    bool detach(InventoryObserver* observer);
    void notify();
    void updateStock();

    // commands that operate on Plant inventory objects
    bool addStock(Plant* plant, int quantity);
    bool removeStock(Plant* plant, int quantity);
    // Execute a stock commands and remove it from memory
    bool executeCommand(StockCommand* command);

private:
    // makes command object friend to allow execution of task on inventory
    friend class AddStock;
    friend class RemoveStock;

    // Find inventory index for a given Plant,
    // if plant not found, returns -1
    int findPlantIndex(Plant* plant) const;
    
};

#endif
