/**
 * @file ItemQueryBuilder.h
 * @brief Concrete builder for creating item-specific Query objects.
 *
 * ItemQueryBuilder constructs Query instances that reference a
 * specific Plant item, such as information or care routine queries.
 *
 * @see Builder
 * @see Query
 * @see Plant
 *
 */
#ifndef ITEMQUERYBULDER_H
#define ITEMQUERYBULDER_H
#include "Plant.h"
#include "Builder.h"
#include"Query.h"
#include<string>

/**
 * @class ItemQueryBuilder
 * @brief Builder class for constructing queries about specific plants.
 */
class ItemQueryBuilder:public Builder{
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
        void setItem(Plant* item);

        ItemQueryBuilder():Builder(){}
};
#endif