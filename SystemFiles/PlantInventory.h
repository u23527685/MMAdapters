#ifndef PLANTINVENTORY_H
#define PLANTINVENTORY_H

#include <string>
#include <vector>
#include <map>
#include "StaffObserver.h"

class PlantInventory {
private:
    std::vector<StaffObserver*> observers;
    std::map<std::string, int> inventory;
    
public:
    PlantInventory();
    ~PlantInventory();
    void attach(StaffObserver* observer);
    void detach(StaffObserver* observer);
    void notify(const std::string& plantType, int quantity);
    void addPlant(const std::string& plantType, int quantity);
    bool removePlant(const std::string& plantType, int quantity);
    int getQuantity(const std::string& plantType) const;
    std::map<std::string, int> getAllInventory() const;
    void displayInventory() const;
};

#endif
