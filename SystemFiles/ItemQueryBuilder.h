/**
 * @file ItemQueryBuilder.h
 * @brief Builder for item-specific Query objects.
 *
 * ItemQueryBuilder constructs Query instances that are targeted at a specific
 * Plant item (e.g. INFO or CARE ROUTINE queries). It implements the Builder
 * interface and stores the item/type/question used to create a Query.
 */
#ifndef ITEMQUERYBULDER_H
#define ITEMQUERYBULDER_H
#include "Builder.h"
#include "Plant.h"
#include "Query.h"
#include <string>

/**
 * @class ItemQueryBuilder
 * @brief Concrete Builder for item-specific queries.
 * @see Builder
 *
 * Use this builder when constructing queries that reference a Plant item.
 */
class ItemQueryBuilder : public Builder
{
    friend Query;

  public:
    /**
     * @brief Set the query type (e.g. "INFO", "CARE ROUTINE").
     * @param type Type string.
     */
    void setType(std::string type);

    /**
     * @brief Set the explicit question text for the query.
     * @param question Question string.
     */
    void setQuestion(std::string question);

    /**
     * @brief Set the Plant item targeted by the query.
     * @param item Non-owning pointer to the Plant.
     */
    void setItem(Plant *item);

    ItemQueryBuilder() : Builder() {}
};
#endif // !ITEMQUERYBULDER_H