#include "FlowerFactory.h"

// Creates and returns a new Flower Plant depending on type
Plant* FlowerFactory::createPlant(std::string plantType = "Rose", double price = 100) {
    if (plantType == "Rose"|| plantType == "rose"|| plantType == "ROSE") {
        return new Rose(price, "Rose");
    }
    else{
        return new Rose(price, "Rose");
    }
    return nullptr;
}
