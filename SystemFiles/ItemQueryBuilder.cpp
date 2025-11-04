/**
 * @file ItemQueryBuilder.cpp
 * @brief Implementation of ItemQueryBuilder setters.
 *
 * These methods configure the builder state (item, type, question) which
 * is later consumed by Builder::build()/Query constructor.
 */

#include "ItemQueryBuilder.h"

/**
 * @brief Set the explicit question text for the item query.
 * @param question Question string.
 */
void ItemQueryBuilder::setQuestion(std::string question)
{
    this->question = question;
}

/**
 * @brief Set the query type for the item query.
 * @param type Type string (e.g. "INFO", "CARE ROUTINE").
 */
void ItemQueryBuilder::setType(std::string type) { this->type = type; }

/**
 * @brief Set the Plant item targeted by the query.
 * @param item Non-owning pointer to the Plant.
 */
void ItemQueryBuilder::setItem(Plant *item) { this->item = item; }