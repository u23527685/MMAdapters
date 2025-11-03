/**
 * @file EmployeeFactory.h
 * @brief Concrete factory for creating regular employees
 */

#ifndef EMPLOYEEFACTORY_H
#define EMPLOYEEFACTORY_H

#include "StaffFactory.h"
#include<string>

/**
 * @class EmployeeFactory
 * @brief Factory that creates regular floor and sales employees
 *
 * This concrete factory implements the StaffFactory interface to create
 * FloorEmployee and SalesEmployee instances.
 *
 * @see StaffFactory
 */
class EmployeeFactory : public StaffFactory {
    public:
        /**
         * @brief Default constructor
         */
        EmployeeFactory();

        /**
         * @brief Virtual destructor
         */
        ~EmployeeFactory();

        /**
         * @brief Create a FloorEmployee instance
         * @param name The name of the employee to create
         * @return Pointer to new FloorEmployee (caller owns memory)
         */
        FloorStaff* createFloorStaff(std::string name) override;

        /**
         * @brief Create a SalesEmployee instance
         * @param name The name of the employee to create
         * @return Pointer to new SalesEmployee (caller owns memory)
         */
        SalesStaff* createSalesStaff(std::string name) override;
};

#endif // !EMPLOYEEFACTORY_H