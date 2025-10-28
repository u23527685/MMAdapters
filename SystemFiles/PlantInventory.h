#ifndef PLANTINVENTORY_H
#define PLANTINVENTORY_H

#include <vector>
#include <string>
#include <iostream>
#include "InventoryObserver.h"

class InventoryObserver;

class PlantInventory {
    public:
        bool attach(InventoryObserver* observer);
        bool detach(InventoryObserver* observer);
        void notify();
        void updateStock();
        
    private:
        std::vector<InventoryObserver*> observers;
};

#endif
