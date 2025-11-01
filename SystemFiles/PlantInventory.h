#ifndef PLANTINVENTORY_H
#define PLANTINVENTORY_H
#include <vector>
#include <string>
#include <algorithm>
#include "InventoryObserver.h"
#include "Plant.h"
#include "StockCommand.h"


/*
-PlantStock and PlantInventory can add and remove stock (it's redundent but works)
-PlantInventory acts as the Receiver in the Command pattern from StockCommand
-Plant inventory has a singleton design pattern implementation 
*/
class PlantInventory {
private:
    // Singleton instance of PlantInventory
    static PlantInventory* instance;

    // List of observers
    std::vector<InventoryObserver*> inventoryObservers;

    // Inventory which contains a pair of Plant pointer and its quantity (key value pair)
    std::vector<std::pair<Plant*, int>> inventoryItems;

    // Constructor made private for singleton design pattern instance of the Class can be obtain using the getInstance method
    PlantInventory();

public:
    // Get singleton instance of the PlantInventory
    static PlantInventory* getInstance();

    ~PlantInventory();//delets observers and inventory

    bool attach(InventoryObserver* observer);
    bool detach(InventoryObserver* observer);
    void notify();//notifies all obsevers if changes made
    void updateStock();

    // commands that operate on Plant inventory objects
    bool addStock(Plant* plant, int quantity);
    bool removeStock(Plant* plant, int quantity);
    
    //when calling addStock and removeStock a command object is created and execteCommand will perform the command and remove it from memory
    bool executeCommand(StockCommand* command);

    // method to access inventory items for command operations only
    std::vector<std::pair<Plant*, int>>& getInventoryReference();

    // method to return a copy not a reference of inventory
    const std::vector<std::pair<Plant*, int>> getInventoryView() const;

    /*
    Find inventory index for a given Plant,
    if plant not found, returns -1
    */
    int findPlantIndex(Plant* plant) const;


    int getQuantity(Plant* plant) const;

};

#endif
