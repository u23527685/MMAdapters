#include "AddStock.h"

AddStock::AddStock(Plant* plant, int quantityToAdd, PlantInventory* targetInventory)
    : plant(plant), quantityToAdd(quantityToAdd), targetInventory(targetInventory) {}

bool AddStock::execute() {
    if (!targetInventory || !plant || quantityToAdd <= 0) {
        return false;
    }

    int idx = targetInventory->findPlantIndex(plant);

    if (idx >= 0) {
        targetInventory->inventoryItems[idx].second += quantityToAdd;
    } else {
        targetInventory->inventoryItems.push_back(std::make_pair(plant, quantityToAdd));
    }

    targetInventory->notify();

    return true;
}
