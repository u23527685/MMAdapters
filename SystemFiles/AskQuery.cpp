/**
 * @file AskQuery.cpp
 * @brief Implementation of AskQuery facade methods for Query creation
 *
 * Contains implementations of describe() and careRoutine() methods that use
 * ItemQueryBuilder to construct specialized Query objects.
 */

#include "AskQuery.h"

/**
 * @brief Creates an INFO Query for a specific Plant
 * @param item Non-owning pointer to the Plant to describe
 * @return Newly allocated Query pointer (caller must delete)
 *
 * Creates and configures an ItemQueryBuilder to construct a Query that
 * requests information about the specified Plant. The temporary builder
 * is deleted after Query construction.
 */
Query *AskQuery::describe(Plant *item)
{
    builder = new ItemQueryBuilder();
    builder->setItem(item);
    builder->setType("INFO");
    Query *q = builder->build();
    delete builder;
    builder = nullptr;
    return q;
}

/**
 * @brief Creates a CARE ROUTINE Query for a specific Plant
 * @param item Non-owning pointer to the Plant to get care info for
 * @return Newly allocated Query pointer (caller must delete)
 *
 * Creates and configures an ItemQueryBuilder to construct a Query that
 * requests care routine information for the specified Plant. The temporary
 * builder is deleted after Query construction.
 */
Query *AskQuery::careRoutine(Plant *item)
{
    builder = new ItemQueryBuilder();
    builder->setItem(item);
    builder->setType("CARE ROUTINE");
    Query *q = builder->build();
    delete builder;
    builder = nullptr;
    return q;
}
