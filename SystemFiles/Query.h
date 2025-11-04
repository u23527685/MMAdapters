/**
 * @file Query.h
 * @brief Represents a query within the plant management system.
 *
 * The Query class encapsulates a specific question or request related
 * to a plant or inventory operation. It is built using the Builder
 * pattern to allow flexible creation of query objects.
 *
 * @see Builder
 * @see Plant
 *
 */

#ifndef QUERY_H
#define QUERY_H
#include "Plant.h"
#include"Builder.h"
#include<string>

/**
 * @class Query
 * @brief Encapsulates a query object constructed by a Builder.
 */

class Query{
    protected:
        Plant* item; ///< The plant associated with this query (optional)
        std::string type; ///< Type of query (e.g., "STOCK", "CARE")
        std::string question; ///< The query text or question detail

    public:
        /**
        * @brief Constructs a Query object from a Builder.
        * @param builder Pointer to a Builder used to initialize the Query.
        */
        Query(Builder* builder);

        /**
        * @brief Gets the type of query.
        * @return The query type as a string.
        */
        std::string getType();

         /**
        * @brief Gets the question text.
        * @return The query question.
        */
        std::string getQuestion();

         /**
        * @brief Gets the plant item associated with the query.
        * @return Pointer to the plant item.
        */
        Plant* getItem(); 

        /**
        * @brief Prints the query information to console.
        */
        void printQuery();
};
#endif