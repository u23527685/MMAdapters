#ifndef STAFFOBSERVER_H
#define SRAFFOBSERVER_H

#include "InventoryObserver.h"
#include <iostream>
#include <string>

class PlantInventory;

class StaffObserver : public InventoryObserver{
    public:
        StaffObserver(PlantInventory* inventory);
        void update();
    
    private:
        PlantInventory* inventory;
};

#endif

