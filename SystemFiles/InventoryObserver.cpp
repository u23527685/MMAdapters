#include "InventoryObserver.h"
#include "PlantInventory.h"
#include <iostream>

InventoryObserver::InventoryObserver(Staff* staff) 
    : associatedStaff(staff) {
    if (staff != nullptr) {
        observerName = staff->getName();
    } else {
        observerName = "Unassigned Observer";
    }
}

InventoryObserver::InventoryObserver(const std::string& name) 
    : associatedStaff(nullptr), observerName(name) {
}

InventoryObserver::~InventoryObserver() {
}

void InventoryObserver::update(PlantInventory* inventory, const std::string& plantType, int quantity) {
    std::cout << "[" << observerName << "] Received inventory update:" << std::endl;
    std::cout << "Plant Type: " << plantType << std::endl;
    std::cout << "Quantity: " << (quantity > 0 ? "+" : "") << quantity << std::endl;
    std::cout << "Current Stock: " << inventory->getQuantity(plantType) << std::endl;
    
    if (quantity > 0) {
        std::cout << "Action: Coordinating with sales floor to display new plants." << std::endl;
        if (associatedStaff != nullptr) {
            std::cout << "Staff member " << associatedStaff->getName() << " is coordinating the restocking." << std::endl;
        }
    } else if (quantity < 0) {
        std::cout << "Action: Plants removed from inventory. Updating sales floor records." << std::endl;
        
        int currentStock = inventory->getQuantity(plantType);
        
        if (currentStock < 5 && currentStock > 0) {
            std::cout << "WARNING: Low stock alert! Only " << currentStock << " " << plantType << "(s) remaining." << std::endl;
        } else if (currentStock == 0) {
            std::cout << "ALERT: " << plantType << " is now OUT OF STOCK!" << std::endl;
        }
    }
    std::cout << std::endl;
}

std::string InventoryObserver::getObserverName() const {
    return observerName;
}

Staff* InventoryObserver::getAssociatedStaff() const {
    return associatedStaff;
}

void InventoryObserver::setAssociatedStaff(Staff* staff) {
    associatedStaff = staff;
    if (staff != nullptr) {
        observerName = staff->getName() + " (Inventory Observer)";
    }
}
