/**
 * @file Builder.h
 * @brief  Builder interface for constructing Query objects.
 *
 * Builder is the abstract base class used by concrete builders such as
 * ItemQueryBuilder and MiscQueryBuilder. It stores the common pieces of
 * state required to construct a Query (item, type, question) and exposes
 * the interface used by the Director classes to configure a Query.
 *
 * Concrete builders implement the setters and may override build() if they
 * need custom construction behaviour.
 */
#ifndef BUILDER_H
#define BUILDER_H
#include "Plant.h"
#include <string>

class Query; // Forward declaration - don't include Query.h here

/**
 * @class Builder
 * @brief Builder class for Query Builders.
 *
 * Holds common fields used during construction and declares the interface
 * for configuring a Query.
 */
class Builder {
  friend class Query; // Use 'class' keyword
protected:
  Plant *item = nullptr;     /**< optional target item for item-specific queries */
  std::string type = "";     /**< type/category of query (e.g. "INFO", "STOCK") */
  std::string question = ""; /**< optional explicit question text */

public:
  /**
   * @brief Set the query type/category.
   * @param type String describing the type (e.g. "INFO", "CARE ROUTINE", "STOCK").
   */
  virtual void setType(std::string type) = 0;

  /**
   * @brief Set the explicit question text for the Query.
   * @param question Question text to include in the Query.
   */
  virtual void setQuestion(std::string question) = 0;

  /**
   * @brief Set the Plant item targeted by the Query.
   * @param item Non-owning pointer to the Plant.
   */
  virtual void setItem(Plant *item) = 0;

  /**
   * @brief Construct a Query from the builder's current state.
   * @return Newly allocated Query instance (caller owns).
   */
  Query *build();

  /**
   * @brief Default constructor initializes members to safe defaults.
   */
  Builder();
};
#endif // BUILDER_H