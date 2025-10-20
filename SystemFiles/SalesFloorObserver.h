#ifndef SALESFLOOROBSERVER_H
#define SALESFLOOROBSERVER_H

#include "InventoryObserver.h"
#include <iostream>

class PlantInventory;

class SalesFloorObserver : public InventoryObserver{
    public:
        SalesFloorObserver(PlantInventory* inv);
        void update();
        
    private:
        PlantInventory* inventory
};

#endif