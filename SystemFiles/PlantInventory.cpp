#include "PlantInventory.h"
#include <iostream>
#include <algorithm>

PlantInventory::PlantInventory() {
}

PlantInventory::~PlantInventory() {
    observers.clear();
}

void PlantInventory::attach(StaffObserver* observer) {
    if (observer != nullptr) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it == observers.end()) {
            observers.push_back(observer);
            std::cout << "Observer " << observer->getObserverName() << " attached to inventory." << std::endl;
        }
    }
}

void PlantInventory::detach(StaffObserver* observer) {
    if (observer != nullptr) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
            std::cout << "Observer " << observer->getObserverName() << " detached from inventory." << std::endl;
        }
    }
}

void PlantInventory::notify(const std::string& plantType, int quantity) {
    std::cout << "Plant Type: " << plantType << ", difference: " << quantity << std::endl;
    
    for (StaffObserver* observer : observers) {
        if (observer != nullptr) {
            observer->update(this, plantType, quantity);
        }
    }
}

void PlantInventory::addPlant(const std::string& plantType, int quantity) {
    if (quantity <= 0) {
        std::cout << "Cannot add non-positive quantity." << std::endl;
        return;
    }
    
    inventory[plantType] += quantity;
    std::cout << "Added " << quantity << " " << plantType << "(s) to inventory. New total: " << inventory[plantType] << std::endl;
    
    notify(plantType, quantity);
}

bool PlantInventory::removePlant(const std::string& plantType, int quantity) {
    if (quantity <= 0) {
        std::cout << "Cannot remove non-positive quantity." << std::endl;
        return false;
    }
    
    if (inventory.find(plantType) == inventory.end() || inventory[plantType] < quantity) {
        std::cout << "Insufficient quantity of " << plantType << " in inventory." << std::endl;
        return false;
    }
    
    inventory[plantType] -= quantity;
    std::cout << "Removed " << quantity << " " << plantType << "(s) from inventory. Remaining: " << inventory[plantType] << std::endl;
    notify(plantType, -quantity);
    
    return true;
}

int PlantInventory::getQuantity(const std::string& plantType) const {
    auto it = inventory.find(plantType);
    if (it != inventory.end()) {
        return it->second;
    }
    return 0;
}

std::map<std::string, int> PlantInventory::getAllInventory() const {
    return inventory;
}

void PlantInventory::displayInventory() const {
    std::cout << "\nPlant Inventory:" << std::endl;
    if (inventory.empty()) {
        std::cout << "Inventory is empty." << std::endl;
    } else {
        for (const auto& item : inventory) {
            std::cout << item.first << ": " << item.second << std::endl;
        }
    }
}
