#include "PlantInventory.h"
#include "InventoryObserver.h"

bool PlantInventory::attach(InventoryObserver* observer) {
    observers.push_back(observer);
    std::cout << "[PlantInventory] Observer attached." << std::endl;
    return true;
}

bool PlantInventory::detach(InventoryObserver* observer) {
    bool found = false;
    int size = observers.size();

    for (int i = 0; i < size; i++) {
        if (observers[i] == observer) {
            observers.erase(observers.begin() + i);
            std::cout << "[PlantInventory] Observer detached." << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "[PlantInventory] Observer not found." << std::endl;
    }

    return found;
}

void PlantInventory::notify() {
    std::cout << "[PlantInventory] Notifying observers..." << std::endl;
    for (size_t i = 0; i < observers.size(); i++) {
        if (observers[i] != nullptr) {
            observers[i]->update();
        }
    }
}

void PlantInventory::updateStock() {
    std::cout << "[PlantInventory] Stock updated." << std::endl;
    notify();
}
