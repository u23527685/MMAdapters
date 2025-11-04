/**
 * @file TreeFactory.cpp
 * @brief Implementation of the TreeFactory class for creating tree plants
 * @author Mthokozisi
 * @date October 25, 2025
 */
#include "TreeFactory.h"

/**
 * @brief Creates a new Tree Plant object
 * @details Factory method that creates and returns a new Oak tree by default,
 *          or when an Oak tree type is specifically requested
 * 
 * @param plantType The type of tree to create (default is "Oak")
 * @param price The price of the tree (default is 100)
 * @return Plant* Pointer to the newly created Plant object
 *         Returns nullptr if creation fails
 * @author Mthokozisi
 */
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
