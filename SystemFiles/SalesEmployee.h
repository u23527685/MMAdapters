/**
 * @file SalesEmployee.h
 * @brief Regular sales staff member implementation
 */

#ifndef SALESEMPLOYEE_H
#define SALESEMPLOYEE_H

#include "SalesStaff.h"
#include <vector>

/**
 * @class SalesEmployee
 * @brief Represents a regular employee in the sales department
 *
 * Handles basic sales queries including stock information, deals,
 * and sales-related questions.
 *
 * @see SalesStaff
 */
class SalesEmployee : public SalesStaff
{
  private:
    std::vector<std::string>
        responsibilities; /**< List of query types this employee can handle */

  public:
    /**
     * @brief Construct a sales employee with given name
     * @param name The employee's name
     */
    SalesEmployee(std::string name);

    /**
     * @brief Virtual destructor
     */
    virtual ~SalesEmployee();

    bool staffCanHandle(std::string type) override;
    void reply(Query *query) override;
};

#endif // !SALESEMPLOYEE_H