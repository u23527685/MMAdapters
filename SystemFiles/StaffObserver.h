#ifndef STAFFOBSERVER_H
#define STAFFOBSERVER_H

#include "InventoryObserver.h"
#include <iostream>

class PlantInventory;

class StaffObserver : public InventoryObserver {
public:
    StaffObserver();
    ~StaffObserver() override;
    void update() override;

private:
    PlantInventory* inventory;
};

#endif
