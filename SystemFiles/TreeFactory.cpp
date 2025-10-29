#include "TreeFactory.h"

// Creates and returns a new Tree Plant
Plant* TreeFactory::createPlant(std::string plantType = "Oak", double price = 100) {
    if (plantType == "Oak" || plantType == "oak" || plantType == "OAK") {
        return new Oak(price, "Oak");
    }
    else{
        return new Oak(price, "Oak");
    }
    return nullptr;
}
