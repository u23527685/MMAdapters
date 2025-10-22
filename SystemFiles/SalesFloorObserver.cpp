#include "SalesFloorObserver.h"
#include "PlantInventory.h"

SalesFloorObserver::SalesFloorObserver(PlantInventory* inventory)
    : InventoryObserver(inventory) {}

void SalesFloorObserver::update() {}
