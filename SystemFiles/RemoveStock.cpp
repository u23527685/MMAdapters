#include "RemoveStock.h"

RemoveStock::RemoveStock(Plant* plant, int quantityToRemove, PlantInventory* targetInventory)
    : plant(plant), quantityToRemove(quantityToRemove), targetInventory(targetInventory) {}

bool RemoveStock::execute() {
    if (!targetInventory || !plant || quantityToRemove <= 0) {
        return false;
    }

    int idx = targetInventory->findPlantIndex(plant);
    if (idx < 0) {
        return false;
    }
    
    auto& inventory = targetInventory->getInventoryReference();
    
    if (inventory[idx].second < quantityToRemove) {
        return false;
    }

    inventory[idx].second -= quantityToRemove;

    if (inventory[idx].second <= 0) {
        delete inventory[idx].first;
        inventory.erase(inventory.begin() + idx);
    }

    return true;
}
