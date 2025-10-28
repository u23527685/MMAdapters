#include "AddStock.h"

AddStock::AddStock(Plant* plant, int quantityToAdd, PlantInventory* targetInventory)
    : plant(plant), quantityToAdd(quantityToAdd), targetInventory(targetInventory) {}

bool AddStock::execute() {
    if (!targetInventory || !plant || quantityToAdd <= 0) {
        return false;
    }

    int idx = targetInventory->findPlantIndex(plant);
    auto& inventory = targetInventory->getInventoryReference();

    if (idx >= 0) {
        inventory[idx].second += quantityToAdd;
    } else {
        inventory.push_back(std::make_pair(plant, quantityToAdd));
    }

    return true;
}
