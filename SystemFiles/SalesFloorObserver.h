#ifndef SALESFLOOROBSERVER_H
#define SALESFLOOROBSERVER_H

#include "InventoryObserver.h"
#include "PlantInventory.h"

class SalesFloorObserver : public InventoryObserver {
public:
    SalesFloorObserver(PlantInventory* inventory);
    void update() override;
};

#endif
