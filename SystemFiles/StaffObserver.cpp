#include "StaffObserver.h"
#include "PlantInventory.h"

StaffObserver::StaffObserver(PlantInventory* inventory) : InventoryObserver(inventory) {}

void StaffObserver::update() {
    // Track inventory changes internally
    const std::vector<std::pair<Plant*, int>> items = inventory->getInventoryView();
}
