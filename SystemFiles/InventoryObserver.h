#ifndef INVENTORYOBSERVER_H
#define INVENTORYOBSERVER_H

class InventoryObserver{
    public:
        virtual void update() = 0;
        virtual ~InventoryObserver();
};

#endif