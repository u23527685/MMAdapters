#include "PlantStock.h"
#include <iostream>

bool PlantStock::addStock(string plantName, int quantity) {
    std::cout << "[PlantStock] Added " << quantity << " of " << plantName << " to inventory." << std::endl;
    return true;
}

bool PlantStock::removeStock(string plantName, int quantity) {
    std::cout << "[PlantStock] Removed " << quantity << " of " << plantName << " from inventory." << std::endl;
    return true;
}
