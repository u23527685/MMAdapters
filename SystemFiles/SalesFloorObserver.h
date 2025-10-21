#ifndef SALESFLOOROBSERVER_H
#define SALESFLOOROBSERVER_H

#include "StaffObserver.h"
#include "Staff.h"
#include <string>
#include <map>

class SalesFloorObserver : public StaffObserver {
private:
    Staff* salesStaff;
    std::string observerName;
    std::map<std::string, int> salesFloorStock;  
public:
    SalesFloorObserver(Staff* staff);
    SalesFloorObserver(const std::string& name); 
    virtual ~SalesFloorObserver();
    void update(PlantInventory* inventory, const std::string& plantType, int quantity) override;
    std::string getObserverName() const override;
    Staff* getSalesStaff() const;
    void updateSalesFloorDisplay(const std::string& plantType, int quantity);
    int getSalesFloorStock(const std::string& plantType) const;
    void displaySalesFloor() const;
};

#endif
