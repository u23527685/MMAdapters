#ifndef STAFFOBSERVER_H
#define STAFFOBSERVER_H

#include "InventoryObserver.h"
#include "PlantInventory.h"
#include <string>
#include <vector>
#include <utility>

class StaffObserver : public InventoryObserver {
private:

public:
    StaffObserver(PlantInventory* inventory);
    void update() override;
    
};
#endif
