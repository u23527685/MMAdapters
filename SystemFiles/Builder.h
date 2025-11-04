/**
 * @file Builder.h
 * @brief Defines the Builder interface for constructing Query objects.
 *
 * The Builder class serves as the base for specific query builders such as
 * ItemQueryBuilder and MiscQueryBuilder. It provides the shared structure
 * and interface used to assemble Query objects.
 *
 *
 * @author 
 * Okaile Gaesale
 */
#ifndef BULDER_H
#define BULDER_H
#include "Plant.h"
#include <string>

class Query;  // Forward declaration

/**
 * @class Builder
 * @brief Abstract builder for constructing Query objects.
 *
 * Provides setters for configuring type, question, and target Plant items.
 * Concrete subclasses customize the construction process.
 */
class Builder{
    friend class Query;  // Use 'class' keyword
    protected:
        Plant* item=nullptr;     /**< optional target item for item-specific queries */
        std::string type="";     /**< type/category of query (e.g. "INFO", "STOCK") */
        std::string question=""; /**< optional explicit question text */
    public:
        /**
         * @brief Set the query type/category.
         * @param type String describing the type (e.g. "INFO", "CARE ROUTINE", "STOCK").
         */
        virtual void setType(std::string type)=0;

        /**
         * @brief Set the explicit question text for the Query.
         * @param question Question text to include in the Query.
         */
        virtual void setQuestion(std::string question)=0;

        /**
         * @brief Set the Plant item targeted by the Query.
         * @param item Non-owning pointer to the Plant.
         */
        virtual void setItem(Plant* item)=0;

        /**
         * @brief Construct a Query from the builder's current state.
         * @return Newly allocated Query instance (caller owns).
         */
        Query* build();

        /**
         * @brief Default constructor initializes members to safe defaults.
         */
        Builder();
};
#endif // !BUILDER_H