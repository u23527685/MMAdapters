/**
 * @file EmployeeFactory.h
 * @brief Concrete factory for creating regular employees.
 *
 * Implements the StaffFactory interface to create instances of FloorEmployee
 * and SalesEmployee.
 *
 * @author 
 * Okaile Gaesale/Cobus Botha/Jay Lopes
 */
#ifndef EMPLOYEEFACTORY_H
#define EMPLOYEEFACTORY_H

#include "StaffFactory.h"
#include<string>

/**
 * @class EmployeeFactory
 * @brief Factory responsible for creating regular staff members.
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