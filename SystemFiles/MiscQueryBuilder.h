/**
 * @file MiscQueryBuilder.h
 * @brief Builder for miscellaneous (non-item) Query objects.
 *
 * MiscQueryBuilder constructs Query instances that are not specific to a
 * Plant item (for example, global stock information). It implements the
 * Builder interface but ignores setItem().
 */
#ifndef MISCQUERYBUILDER_H
#define MISCQUERYBUILDER_H
#include "Builder.h"
#include "Plant.h"
#include "Query.h"
#include <string>

/**
 * @class MiscQueryBuilder
 * @brief Concrete Builder for miscellaneous queries.
 * @see Builder
 *
 * Implements the Builder interface for queries that do not target a specific
 * Plant item. The builder stores the configured type/question and produces
 * a Query via Builder::build().
 */
class MiscQueryBuilder : public Builder
{
    friend Query;

  public:
    /**
     * @brief Set the query type for the miscellaneous query.
     * @param type Type string (e.g. "STOCK").
     */
    void setType(std::string type) override;

    /**
     * @brief Set the explicit question text.
     * @param question Question string.
     */
    void setQuestion(std::string question) override;

    /**
     * @brief setItem has no effect for MiscQueryBuilder.
     * @param item Ignored.
     */
    void setItem(Plant *item) override;

    MiscQueryBuilder() : Builder() {}
};
#endif // !MISCQUERYBUILDER_H