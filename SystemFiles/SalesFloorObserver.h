#ifndef SALESFLOOROBSERVER_H
#define SALESFLOOROBSERVER_H

#include "InventoryObserver.h"
#include <iostream>

class SalesFloorObserver : public InventoryObserver {
public:
    SalesFloorObserver();
    ~SalesFloorObserver() override;
    void update() override;
};

#endif