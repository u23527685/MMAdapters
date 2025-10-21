#include "StaffObserver.h"
#include "PlantInventory.h"

StaffObserver::StaffObserver(PlantInventory* inventory) : inventory(inventory){}

void StaffObserver::update(){
    std::cout << "[StaffObserver] Inventory updated for staff." << std::endl;
}
