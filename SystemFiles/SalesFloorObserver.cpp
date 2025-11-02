#include "SalesFloorObserver.h"
#include "PlantInventory.h"
#include "Staff.h"
#include <iostream>
#include <algorithm>
#include <map>

SalesFloorObserver::SalesFloorObserver(PlantInventory* inventory) : InventoryObserver(inventory) {
    if(inventory){
        inventory->attach(this);
        update();
    }
}

void SalesFloorObserver::update() {
    //Save old state for comparison
    std::vector<std::pair<Plant*, int>> oldItems = availableItems;
    
    //Get current inventory and update availableItems
    const std::vector<std::pair<Plant*, int>> items = inventory->getInventoryView();
    availableItems.clear();
    
    for (const auto& item : items) {
        if (item.second > 0) {
            availableItems.push_back(item);
            plantDescriptions[item.first] = item.first->getDescription();
        }
    }

    std::cout << "Sales Floor Update: " << availableItems.size() << " plant types currently available." << std::endl;
    
    //Determine what changed and notify staff
    for (const auto& newItem : availableItems) {
        Plant* plant = newItem.first;
        int newQty = newItem.second;
        
        //Find old quantity
        int oldQty = 0;
        for (const auto& oldItem : oldItems) {
            if (oldItem.first == plant) {
                oldQty = oldItem.second;
                break;
            }
        }
        
        //If this is new or quantity increased
        if (oldQty == 0) {
            std::string message = "New stock added: " + plant->getDescription() + " (Qty: " + std::to_string(newQty) + ")";
            notifyStaff(message);
        } else if (newQty > oldQty) {
            int added = newQty - oldQty;
            std::string message = "Stock added: " + std::to_string(added) + " " + plant->getDescription() + " (Total: " + std::to_string(newQty) + ")";
            notifyStaff(message);
        } else if (newQty < oldQty) {
            int removed = oldQty - newQty;
            std::string message = "Stock removed: " + std::to_string(removed) + " " + plant->getDescription() + " (Remaining: " + std::to_string(newQty) + ")";
            notifyStaff(message);
        }
    }
    
    //Check for items that were completely removed (went to 0)
    for (const auto& oldItem : oldItems) {
        Plant* plant = oldItem.first;
        bool found = false;
        
        for (const auto& newItem : availableItems) {
            if (newItem.first == plant) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            // Use the cached description from when the plant existed
            std::string description = plantDescriptions.count(plant) > 0 
                ? plantDescriptions[plant] 
                : "Unknown Plant";
            std::string message = "Stock depleted: " + description + " is now out of stock";
            notifyStaff(message);
        }
    }
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
