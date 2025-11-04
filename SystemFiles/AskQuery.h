/**
 * @file AskQuery.h
 * @brief Director for creating different types of Query objects using builders
 *
 * This class provides a simplified interface for creating Query objects using
 * the Builder pattern. It handles the details of choosing and configuring the
 * appropriate builder (ItemQueryBuilder or MiscQueryBuilder) based on the
 * type of query needed.
 */

#ifndef ASKQUERY_H
#define ASKQUERY_H

#include "Builder.h"
#include "FloorStaff.h"
#include "ItemQueryBuilder.h"
#include "MiscQueryBuilder.h"
#include "Plant.h"
#include "Query.h"
#include <string>

/**
 * @class AskQuery
 * @brief Director class that simplifies Query object creation using builders
 *
 * This class manages temporary Builder instances to construct Query objects.
 * It abstracts the builder selection and configuration process, providing
 * simple methods for common query types.
 */
class AskQuery
{
  private:
    Builder *builder; /**< Temporary builder used during Query construction */

  public:
    /**
     * @brief Creates a Query requesting description of a specific Plant
     * @param item Pointer to the Plant to describe (non-owning)
     * @return Newly allocated Query object (caller takes ownership)
     *
     * Uses ItemQueryBuilder to create an INFO-type Query targeting the
     * specified Plant.
     */
    Query *describe(Plant *item);

    /**
     * @brief Creates a Query requesting care routine for a specific Plant
     * @param item Pointer to the Plant to get care info for (non-owning)
     * @return Newly allocated Query object (caller takes ownership)
     *
     * Uses ItemQueryBuilder to create a CARE ROUTINE-type Query targeting
     * the specified Plant.
     */
    Query *careRoutine(Plant *item);
};

#endif // !ASKQUERY_H