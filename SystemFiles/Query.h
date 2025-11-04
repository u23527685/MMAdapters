/**
 * @file Query.h
 * @brief Header file for the Query class
 * @author okaile
 * @date October 27, 2025
 */

#ifndef QUERY_H
#define QUERY_H

#include "Builder.h"
#include "Plant.h"
#include <string>

/**
 * @class Query
 * @brief Class representing a query about a plant
 * @details Handles plant-related queries and stores query information
 * @author Kai
 */
class Query
{
  protected:
    Plant *item;
    std::string type;
    std::string question;

  public:
    /**
     * @brief Constructor for Query
     * @param builder Pointer to the Builder object that constructs the query
     * @return None (constructor)
     * @author Kai
     */
    Query(Builder *builder);

    /**
     * @brief Gets the type of query
     * @return std::string The query type
     * @author Kai
     */
    std::string getType();

    /**
     * @brief Gets the query question
     * @return std::string The query question
     * @author Kai
     */
    std::string getQuestion();

    /**
     * @brief Gets the plant item associated with the query
     * @return Plant* Pointer to the plant item
     * @author Kai
     */
    Plant *getItem();

    /**
     * @brief Prints the query details
     * @return void
     * @author Kai
     */
    void printQuery();
};

#endif