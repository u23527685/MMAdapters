#ifndef INVENTORYOBSERVER_H
#define INVENTORYOBSERVER_H

#include "Plant.h"

class PlantInventory;

class InventoryObserver {
protected:
    PlantInventory* inventory;
public:
    InventoryObserver(PlantInventory* inventory);
    virtual ~InventoryObserver();
    virtual void update() = 0;
};

#endif
