#ifndef STAFFOBSERVER_H
#define STAFFOBSERVER_H

#include "InventoryObserver.h"
#include "PlantInventory.h"
#include <string>

class StaffObserver : public InventoryObserver {
public:
    StaffObserver(PlantInventory* inventory);
    void update() override;
};

#endif
