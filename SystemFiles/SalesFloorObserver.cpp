#include "SalesFloorObserver.h"
#include "PlantInventory.h"
#include <iostream>


SalesFloorObserver::SalesFloorObserver(PlantInventory* inv) : inventory(inv) {}

void SalesFloorObserver::update() {
    std::cout << "[SalesFloorObserver] Inventory updated for sales floor." << std::endl;
}
