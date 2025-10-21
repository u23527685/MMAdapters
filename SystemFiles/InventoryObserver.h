#ifndef INVENTORYOBSERVER_H
#define INVENTORYOBSERVER_H

#include "StaffObserver.h"
#include "Staff.h"
#include <string>

class InventoryObserver : public StaffObserver {
private:
    Staff* associatedStaff;
    std::string observerName; 
public:
    InventoryObserver(Staff* staff);
    InventoryObserver(const std::string& name);
    virtual ~InventoryObserver();
    void update(PlantInventory* inventory, const std::string& plantType, int quantity) override;
    std::string getObserverName() const override;
    Staff* getAssociatedStaff() const;
    void setAssociatedStaff(Staff* staff);
};

#endif
