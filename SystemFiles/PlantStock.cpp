#include "PlantStock.h"

//PlantStock::PlantStock(){}

bool PlantStock::addStock(std::string plantName, int quantity) {
    inventory[plantName] += quantity;
    std::cout << "[PlantStock] Added " << quantity << " of " << plantName << " to inventory. New total: "<< inventory[plantName] << std::endl;
    return true;
}

bool PlantStock::removeStock(std::string plantName, int quantity) {
    if(inventory.find(plantName) == inventory.end() || inventory[plantName] < quantity){
        std::cout << "[PlantStock] Insufficient stock for " << plantName << std::endl;
        return false;
    }
    std::cout << "[PlantStock] Removed " << quantity << " of " << plantName << " from inventory. Remaining: "<< inventory[plantName] << std::endl;
    return true;
}

int PlantStock::getQuantity(std::string plantName) const {
    auto it = inventory.find(plantName);
    if(it != inventory.end()){
        return it->second;
    }
    return 0;
}

void PlantStock::displayInventory() const{
    std::cout << "CURRENT INVENTORY:" << std::endl;
    for(const auto& pair : inventory){
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}