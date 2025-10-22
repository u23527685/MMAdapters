#include "StaffObserver.h"
#include "StaffObserver.h"
#include "PlantInventory.h"

StaffObserver::StaffObserver(PlantInventory* inventory)
    : InventoryObserver(inventory) {}

void StaffObserver::update() {}
