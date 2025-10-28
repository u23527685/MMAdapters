#include "FlowerFactory.h"

// Creates and returns a new Flower Plant depending on type
Plant* FlowerFactory::createPlant(std::string plantType, double price) {
    if (plantType == "Rose"|| plantType == "rose"|| plantType == "ROSE"|| plantType == "r"|| plantType == "R") {
        return new Rose(price, plantType);
    }
    else{
        return new Rose(price, plantType);
    }
    return nullptr;
}
