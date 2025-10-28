#include "SalesFloorObserver.h"
#include "PlantInventory.h"
#include "Staff.h"
#include <iostream>
#include <algorithm>

SalesFloorObserver::SalesFloorObserver(PlantInventory* inventory) : InventoryObserver(inventory) {
    update();
}

void SalesFloorObserver::update() {
    // Track only available items if their quantity is greater than zero
    const std::vector<std::pair<Plant*, int>> items = inventory->getInventoryView();
    availableItems.clear();
    
    for (const auto& item : items) {
        if (item.second > 0) {
            availableItems.push_back(item);
        }
    }

    std::cout << "Sales Floor Update: " << availableItems.size() << " plant types currently available." << std::endl;
    
    //notify all registered staff members
    std::string message = "Inventory updated: " + std::to_string(availableItems.size()) + " plant types available.";
    notifyStaff(message);
}

bool SalesFloorObserver::isPlantAvailable(Plant* plant) const {
    for (const auto& item : availableItems) {
        if (item.first == plant && item.second > 0) {
            return true;
        }
    }
    return false;
}

int SalesFloorObserver::getPlantQuantity(Plant* plant) const {
    for (const auto& item : availableItems) {
        if (item.first == plant) {
            return item.second;
        }
    }
    return 0;
}

void SalesFloorObserver::displayAvailablePlants() const {
    std::cout << "\n=============== SALES FLOOR INVENTORY ===============" << std::endl;
    
    if (availableItems.empty()) {
        std::cout << "No plants currently available on sales floor." << std::endl;
        std::cout << "====================================================\n" << std::endl;
        return;
    }

    int totalCount = 0;
    double totalValue = 0.0;
    
    std::cout << std::left;
    std::cout << "----------------------------------------------------" << std::endl;
    
    for (const auto& item : availableItems) {
        Plant* plant = item.first;
        
        if (!isPlantAvailable(plant)) {
            continue;
        }
        
        int quantity = getPlantQuantity(plant);
        double itemValue = plant->getPrice() * quantity;
        
        totalCount += quantity;
        totalValue += itemValue;
        
        std::cout << plant->getDescription() << std::endl;
        std::cout << "   Price: R" << plant->getPrice() << " | Quantity: " << quantity << " | Subtotal: R" << itemValue << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
    }
    
    std::cout << "SUMMARY:" << std::endl;
    std::cout << "   Total Plant Types: " << availableItems.size() << std::endl;
    std::cout << "   Total Plants: " << totalCount << std::endl;
    std::cout << "   Inventory Value: R" << totalValue << std::endl;
    std::cout << "====================================================\n" << std::endl;
}

void SalesFloorObserver::attachStaff(Staff* staff) {
    if (staff) {
        notifiedStaff.push_back(staff);
        std::cout << "Staff member " << staff->getName() << " attached to sales floor observer." << std::endl;
    }
}

void SalesFloorObserver::detachStaff(Staff* staff) {
    auto it = std::find(notifiedStaff.begin(), notifiedStaff.end(), staff);
    if (it != notifiedStaff.end()) {
        std::cout << "Staff member " << (*it)->getName() << " detached from sales floor observer." << std::endl;
        notifiedStaff.erase(it);
    }
}

void SalesFloorObserver::notifyStaff(const std::string& message) {
    for (Staff* staff : notifiedStaff) {
        std::cout << "  [Notification to " << staff->getName() << "] " << message << std::endl;
    }
}
