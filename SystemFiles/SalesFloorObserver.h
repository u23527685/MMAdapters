#ifndef SALESFLOOROBSERVER_H
#define SALESFLOOROBSERVER_H

#include "InventoryObserver.h"
#include "PlantInventory.h"
#include "Staff.h"
#include <vector>
#include <utility>
#include <string>
#include <map>

class SalesFloorObserver : public InventoryObserver {
private:
    std::vector<std::pair<Plant*, int>> availableItems;
    std::vector<Staff*> notifiedStaff;
    std::map<Plant*, std::string> plantDescriptions;
    
public:
    SalesFloorObserver(PlantInventory* inventory);
    void update() override;
    void displayAvailablePlants() const;
    bool isPlantAvailable(Plant* plant) const;
    const std::vector<std::pair<Plant*, int>>& getAvailableItems() const {
        return availableItems;
    }
    int getPlantQuantity(Plant* plant) const;
    
    void attachStaff(Staff* staff);
    void detachStaff(Staff* staff);
    void notifyStaff(const std::string& message);
};

#endif
