#include "StaffObserver.h"
#include "PlantInventory.h"
#include <iostream>

StaffObserver::StaffObserver(PlantInventory* inv) : inventory(inv){}

void StaffObserver::update(){
    std::cout << "[StaffObserver] Inventory updated for staff." << std::endl;
}