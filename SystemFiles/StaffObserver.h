#ifndef STAFFOBSERVER_H
#define SRAFFOBSERVER_H

#include "InventoryObserver.h"
#include <iostream>

class PlantInventory;

class StaffObserver : public InventoryObserver{
    public:
        StaffObserver(PlantInventory* inv);
        void update();
    
    private:
        PlantInventory* inventory;
};

#endif