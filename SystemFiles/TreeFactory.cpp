#include "TreeFactory.h"

// Creates and returns a new Tree Plant
Plant* TreeFactory::createPlant(std::string plantType, double price) {
    if (plantType == "Oak" || plantType == "oak" || plantType == "OAK" || plantType == "o" || plantType == "O") {
        return new Oak(price, plantType);
    }
    else{
        return new Oak(price, plantType);
    }
    return nullptr;
}
