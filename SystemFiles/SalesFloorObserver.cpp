#include "SalesFloorObserver.h"
#include "PlantInventory.h"

SalesFloorObserver::SalesFloorObserver(PlantInventory* inventory)
    : InventoryObserver(inventory) {}

void SalesFloorObserver::update() {
    // Track only available items if their quantity is greater than zero
    const std::vector<std::pair<Plant*, int>> items = inventory->getInventoryView();
    availableItems.clear();
    
    for (const auto& item : items) {
        if (item.second > 0) {
            availableItems.push_back(item);
        }
    }
}
