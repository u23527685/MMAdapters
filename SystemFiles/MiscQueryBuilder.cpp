/**
 * @file MiscQueryBuilder.cpp
 * @brief Implementation of MiscQueryBuilder methods.
 *
 * Implements setters for the type/question. setItem is intentionally a no-op
 * because miscellaneous queries do not target a specific Plant.
 */

#include"MiscQueryBuilder.h"
#include <iostream>

/**
 * @brief Set the explicit question text for the misc query.
 * @param question Question string.
 */
void MiscQueryBuilder::setQuestion(std::string question){
    this->question=question;
}

/**
 * @brief Set the type/category for the misc query.
 * @param type Type string (e.g. "STOCK").
 */
void MiscQueryBuilder::setType(std::string type){
    this->type=type;
}

/**
 * @brief setItem is not supported for miscellaneous queries.
 * @param item Ignored.
 *
 * This implementation intentionally does not store the provided item. A
 * diagnostic message is printed to stderr to aid debugging.
 */
void MiscQueryBuilder::setItem(Plant* item){
    std::cerr<<"MiscQueryBuilder::setItem(): miscellaneous queries do not support an item\n";
}