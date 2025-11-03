#include "SalesFloorObserver.h"
#include "PlantInventory.h"
#include "Staff.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>

SalesFloorObserver::SalesFloorObserver(PlantInventory* inventory) : InventoryObserver(inventory) {
    if (inventory) {
        inventory->attach(this);
        update();
    }
}


void SalesFloorObserver::update() {
    if (!inventory) {
        return;
    }

    std::vector<std::pair<Plant*, int>> oldItems = availableItems;
    availableItems.clear();

    const auto items = inventory->getInventoryView();
    for (const auto& item : items) {
        if (item.first && item.second > 0) {
            availableItems.push_back(item);
        }
    }

    // Count unique plant types
    std::set<std::string> plantTypes;
    for (const auto& item : availableItems) {
        if (item.first) {
            plantTypes.insert(item.first->getDescription());
        }
    }
    std::cout << "Sales Floor Update: " << plantTypes.size() << " plant types currently available." << std::endl;

    for (const auto& newItem : availableItems) {
        Plant* plant = newItem.first;
        if (!plant) continue;
        int newQty = newItem.second;
        int oldQty = 0;
        for (const auto& oldItem : oldItems) {
            if (oldItem.first && oldItem.first->getDescription() == plant->getDescription()) {
                oldQty = oldItem.second;
                break;
            }
        }

        std::string description = plant->getDescription();
        if (oldQty == 0) {
            std::string message = "New stock added: " + description + " (Qty: " + std::to_string(newQty) + ")";
            notifyStaff(message);
        } else if (newQty > oldQty) {
            int added = newQty - oldQty;
            std::string message = "Stock added: " + std::to_string(added) + " " + description + " (Total: " + std::to_string(newQty) + ")";
            notifyStaff(message);
        } else if (newQty < oldQty) {
            int removed = oldQty - newQty;
            std::string message = "Stock removed: " + std::to_string(removed) + " " + description + " (Remaining: " + std::to_string(newQty) + ")";
            notifyStaff(message);
        }
    }

    for (const auto& oldItem : oldItems) {
        if (!oldItem.first) continue;
        bool found = false;
        for (const auto& newItem : availableItems) {
            if (newItem.first && newItem.first->getDescription() == oldItem.first->getDescription()) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::string description = oldItem.first->getDescription();
            std::string message = "Stock depleted: " + description + " is now out of stock";
            notifyStaff(message);
        }
    }
}

bool SalesFloorObserver::isPlantAvailable(Plant* plant) const {
    if (!plant) return false;
    for (const auto& item : availableItems) {
        if (item.first && item.first->getDescription() == plant->getDescription() && item.second > 0) {
            return true;
        }
    }
    return false;
}

int SalesFloorObserver::getPlantQuantity(Plant* plant) const {
    if (!plant) return 0;
    for (const auto& item : availableItems) {
        if (item.first && item.first->getDescription() == plant->getDescription()) {
            return item.second;
        }
    }
    return 0;
}

void SalesFloorObserver::displayAvailablePlants() const {
    std::cout << "\n=============== SALES FLOOR INVENTORY ===============\n";
    if (availableItems.empty()) {
        std::cout << "No plants currently available on sales floor.\n";
        std::cout << "===================================================\n\n";
        return;
    }

    int totalCount = 0;
    double totalValue = 0.0;
    std::map<std::string, std::pair<Plant*, int>> consolidatedItems;
    
    // Consolidate items by description
    for (const auto& item : availableItems) {
        if (!item.first || item.second <= 0) continue;
        std::string desc = item.first->getDescription();
        if (consolidatedItems.find(desc) == consolidatedItems.end()) {
            consolidatedItems[desc] = {item.first, item.second};
        } else {
            consolidatedItems[desc].second += item.second;
        }
    }

    std::cout << std::left << "----------------------------------------------------\n";
    for (const auto& pair : consolidatedItems) {
        Plant* plant = pair.second.first;
        int quantity = pair.second.second;
        double itemValue = plant->getPrice() * quantity;
        totalCount += quantity;
        totalValue += itemValue;
        std::cout << plant->getDescription() << "\n";
        std::cout << "   Price: R" << plant->getPrice() << " | Quantity: " << quantity << " | Subtotal: R" << itemValue << "\n";
        std::cout << "----------------------------------------------------\n";
    }
    std::cout << "SUMMARY:\n";
    std::cout << "   Total Plant Types: " << consolidatedItems.size() << "\n";
    std::cout << "   Total Plants: " << totalCount << "\n";
    std::cout << "   Total Value: R" << totalValue << "\n";
    std::cout << "===================================================\n\n";
}

void SalesFloorObserver::attachStaff(Staff* staff) {
    if (staff && std::find(notifiedStaff.begin(), notifiedStaff.end(), staff) == notifiedStaff.end()) {
        notifiedStaff.push_back(staff);
    }
}

void SalesFloorObserver::detachStaff(Staff* staff) {
    auto it = std::find(notifiedStaff.begin(), notifiedStaff.end(), staff);
    if (it != notifiedStaff.end()) {
        notifiedStaff.erase(it);
    }
}

void SalesFloorObserver::notifyStaff(const std::string& message) {
    notificationHistory.push_back(message);
    for (Staff* staff : notifiedStaff) {
        if (staff) {
            std::cout << "Notifying " << staff->getName() << ": " << message << std::endl;
        }
    }
}
