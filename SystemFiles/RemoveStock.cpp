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
    if (targetInventory->inventoryItems[idx].second < quantityToRemove) {
        return false;
    }

    targetInventory->inventoryItems[idx].second -= quantityToRemove;

    if (targetInventory->inventoryItems[idx].second <= 0) {
        delete targetInventory->inventoryItems[idx].first;
        targetInventory->inventoryItems.erase(targetInventory->inventoryItems.begin() + idx);
    }

    targetInventory->notify();

    return true;
}
