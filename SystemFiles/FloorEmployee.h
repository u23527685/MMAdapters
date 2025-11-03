/**
 * @file FloorEmployee.h
 * @brief Regular floor staff member implementation
 */

#ifndef FLOOREMPLOYEE_H
#define FLOOREMPLOYEE_H

#include "FloorStaff.h"
#include<vector>
#include<string>

/**
 * @class FloorEmployee
 * @brief Represents a regular employee on the shop floor
 * 
 * Handles customer-facing queries about plants, including care
 * instructions and general information.
 * 
 * @see FloorStaff
 */
class FloorEmployee : public FloorStaff {
    private:
        std::vector<std::string> responsibilities; /**< List of query types this employee can handle */
    
    public:
        /**
         * @brief Construct a floor employee with given name
         * @param name The employee's name
         */
        FloorEmployee(std::string name);
        
        /**
         * @brief Virtual destructor
         */
        virtual ~FloorEmployee();
        
        bool staffCanHandle(std::string type) override;
        void reply(Query* query) override;
};

#endif // !FLOOREMPLOYEE_H