#include "InventoryObserver.h"
#include "PlantInventory.h"

InventoryObserver::InventoryObserver(PlantInventory* inventory)
    : inventory(inventory) {
    if (inventory) {
        inventory->attach(this);
    }
}

InventoryObserver::~InventoryObserver() {
    if (inventory) {
        inventory->detach(this);
    }
}

