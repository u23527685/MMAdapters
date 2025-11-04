/**
 * @file SalesEmployee.h
 * @brief Defines a regular employee in the sales department.
 *
 * The SalesEmployee class handles basic sales queries and
 * supports chain-of-responsibility query delegation.
 *
 * @see SalesStaff
 * @see SalesManager
++
 */

#ifndef SALESEMPLOYEE_H
#define SALESEMPLOYEE_H

#include "SalesStaff.h"
#include<vector>

/**
 * @class SalesEmployee
 * @brief Concrete class representing a regular sales employee.
 */
class SalesEmployee : public SalesStaff {
    private:
        std::vector<std::string> responsibilities; ///< List of query types this employee can handle.
    
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
        void reply(Query* query) override;
};

#endif 