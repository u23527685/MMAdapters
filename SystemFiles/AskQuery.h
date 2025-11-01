/**
 * @file AskQuery.h
 * @brief Director for creating commonly asked Query objects for plants and stock.
 *
 * This header declares AskQuery,the Director class that constructs commonly asked Query
 * objects using concrete Builder implementations (ItemQueryBuilder,
 * MiscQueryBuilder). It centralizes creation of Query instances for:
 *  - item description queries
 *  - care routine queries
 *  - stock information queries
 *
 * The caller takes ownership of the returned Query* and is responsible
 * for deleting it.
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
 * @brief Director class to construct commonly asked Query objects using builders.
 *
 * AskQuery holds a temporary Builder* used to configure and build
 * Query objects. Each public method allocates a concrete builder,
 * uses it to create a Query, deletes the builder, and returns the
 * built Query pointer.
 */
class AskQuery{
    private:
        Builder* builder; /**< temporary builder used during construction */
    public:
        /**
         * @brief Create an "INFO" Query for a given Plant.
         * @param item Pointer to the Plant to describe (non-owning).
         * @return Pointer to a newly allocated Query. Caller owns and must delete it.
         */
        Query* describe(Plant* item);

        /**
         * @brief Create a "CARE ROUTINE" Query for a given Plant.
         * @param item Pointer to the Plant for which to create the care routine query (non-owning).
         * @return Pointer to a newly allocated Query. Caller owns and must delete it.
         */
        Query* careRoutine(Plant* item);

        /**
         * @brief Create a "STOCK" Query (miscellaneous stock information).
         * @return Pointer to a newly allocated Query. Caller owns and must delete it.
         */
        Query* stockInfo();
};

#endif // !ASKQUERY_H