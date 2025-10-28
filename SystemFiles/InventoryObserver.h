#ifndef INVENTORY_OBSERVER_H
#define INVENTORY_OBSERVER_H

class InventoryObserver {
public:
    virtual ~InventoryObserver();
    virtual void update() = 0;
};

#endif
