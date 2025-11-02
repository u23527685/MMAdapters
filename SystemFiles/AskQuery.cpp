/**
 * @file AskQuery.cpp
 * @brief Implementation of AskQuery methods that build Query objects.
 *
 * Uses ItemQueryBuilder and MiscQueryBuilder to construct Query instances.
 */

#include "AskQuery.h"

/**
 * @brief Build a Query that provides descriptive information for a Plant.
 * @param item Non-owning pointer to the Plant to describe.
 * @return Newly allocated Query pointer (caller must delete).
 */
Query* AskQuery::describe(Plant* item){
    builder = new ItemQueryBuilder();
    builder->setItem(item);
    builder->setType("INFO");
    Query *q = builder->build();
    delete builder;
    return q;
}

/**
 * @brief Build a Query that provides the care routine for a Plant.
 * @param item Non-owning pointer to the Plant whose care routine is requested.
 * @return Newly allocated Query pointer (caller must delete).
 */
Query* AskQuery::careRoutine(Plant* item){
    builder = new ItemQueryBuilder();
    builder->setItem(item);
    builder->setType("CARE ROUTINE");
    Query *q = builder->build();
    delete builder;
    return q;
}

/**
 * @brief Build a Query that provides stock information (misc).
 * @return Newly allocated Query pointer (caller must delete).
 */
Query* AskQuery::stockInfo(){
    builder = new MiscQueryBuilder();
    builder->setType("STOCK");
    Query *q = builder->build();
    delete builder;
    return q;
}