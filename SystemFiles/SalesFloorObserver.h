#ifndef SALESFLOOROBSERVER_H
#define SALESFLOOROBSERVER_H

#include "InventoryObserver.h"
#include "PlantInventory.h"
#include <vector>
#include <utility>

class SalesFloorObserver : public InventoryObserver {
private:
    std::vector<std::pair<Plant*, int>> availableItems;

public:
    SalesFloorObserver(PlantInventory* inventory);
    void update() override;
    
    // Method to get currently available items from inventory
    const std::vector<std::pair<Plant*, int>>& getAvailableItems() const {
        return availableItems;
    }
};
#endif
