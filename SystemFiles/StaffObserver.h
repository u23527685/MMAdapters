#ifndef STAFFOBSERVER_H
#define STAFFOBSERVER_H

#include <string>

class PlantInventory;

class StaffObserver {
public:
    virtual ~StaffObserver() {}
    virtual void update(PlantInventory* inventory, const std::string& plantType, int quantity) = 0;
    virtual std::string getObserverName() const = 0;
};

#endif
