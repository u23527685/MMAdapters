#ifndef INVENTORYOBSERVER_H
#define INVENTORYOBSERVER_H

#include <iostream>
#include <string>

class InventoryObserver{
    public:
        virtual void update() = 0;
        virtual ~InventoryObserver();
};

#endif

