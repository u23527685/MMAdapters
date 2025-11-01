#ifndef INVENTORYPROXY_H
#define INVENTORYPROXY_H

#include "PlantInventory.h"
#include "SalesFloorObserver.h"
#include <stdexcept>
#include <string>


class InventoryProxy {
    PlantInventory* inventory;
    SalesFloorObserver* salesObserver;
public:
    InventoryProxy(SalesFloorObserver* observer);

    void buyPlant(Plant* plant, int quantity);

    void addStock(Plant* plant, int quantity);
    void removeStock(Plant*, int);

    void displayAvailablePlants() const {
        if (salesObserver) salesObserver->displayAvailablePlants();
    }
};

#endif
