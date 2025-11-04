/**
 * @file MiscQueryBuilder.h
 * @brief Builder for creating general (non-item-specific) queries.
 *
 * Constructs Query instances that are not tied to a specific Plant object,
 * such as global stock inquiries or system-wide data requests.
 *
 * @author 
 * Okaile Gaesale
 */
#ifndef MISCQUERYBUILDER_H
#define MISCQUERYBUILDER_H
#include "Plant.h"
#include "Builder.h"
#include"Query.h"
#include<string>

/**
 * @class MiscQueryBuilder
 * @brief Concrete builder for non-item queries.
 * @see Builder
 *
 * Implements Builder but ignores setItem() since it targets no specific Plant.
 */
class MiscQueryBuilder:public Builder{
    friend Query;
    public:
        /**
         * @brief Set the query type for the miscellaneous query.
         * @param type Type string (e.g. "STOCK").
         */
        void setType(std::string type)override;

        /**
         * @brief Set the explicit question text.
         * @param question Question string.
         */
        void setQuestion(std::string question)override;

        /**
         * @brief setItem has no effect for MiscQueryBuilder.
         * @param item Ignored.
         */
        void setItem(Plant* item)override;

        /**
        * @brief Constructs a new MiscQueryBuilder.
        */
        MiscQueryBuilder():Builder(){}
};
#endif