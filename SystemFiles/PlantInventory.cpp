#include "PlantInventory.h"
#include "AddStock.h"
#include "RemoveStock.h"

PlantInventory* PlantInventory::instance = nullptr;

PlantInventory::PlantInventory() {}

PlantInventory* PlantInventory::getInstance() {
    if (instance == nullptr) {
        instance = new PlantInventory();
    }
    return instance;
}

PlantInventory::~PlantInventory() {
    for (std::pair<Plant*, int> &item : inventoryItems) {
        delete item.first;
    }
    for (InventoryObserver* observer : inventoryObservers) {
        delete observer;
    }
}

bool PlantInventory::attach(InventoryObserver* observer) {
    inventoryObservers.push_back(observer);
    return true;
}

bool PlantInventory::detach(InventoryObserver* observer) {
    auto it = std::find(inventoryObservers.begin(), inventoryObservers.end(), observer);
    if (it != inventoryObservers.end()) {
        inventoryObservers.erase(it);
        return true;
    }
    return false;
}

void PlantInventory::notify() {
    for (InventoryObserver* observer : inventoryObservers) {
        observer->update();
    }
}

void PlantInventory::updateStock() {
    notify();
}

int PlantInventory::findPlantIndex(Plant* plant) const {
    for (size_t i = 0; i < inventoryItems.size(); ++i) {
        if (inventoryItems[i].first == plant) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

//execute given command and removes it from memory
bool PlantInventory::executeCommand(StockCommand* command) {
    if (!command) {
        return false;
    }

    bool executionResults = command->execute();

    delete command;

    return executionResults;
}

bool PlantInventory::addStock(Plant* plant, int quantity) {
    AddStock* addCommand = new AddStock(plant, quantity, this);
    return executeCommand(addCommand);
}

bool PlantInventory::removeStock(Plant* plant, int quantity) {
    RemoveStock* removeCommand = new RemoveStock(plant, quantity, this);
    return executeCommand(removeCommand);
}

std::vector<std::pair<Plant*, int>>& PlantInventory::getInventoryReference() {
    return inventoryItems;
}

const std::vector<std::pair<Plant*, int>> PlantInventory::getInventoryView() const {
    return inventoryItems;
}
