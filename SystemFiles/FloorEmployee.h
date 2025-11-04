/**
 * @file FloorEmployee.h
 * @brief Concrete class representing a floor employee.
 *
 * Handles basic customer interactions such as providing plant care
 * information and general inquiries.
 *
 */
#ifndef FLOOREMPLOYEE_H
#define FLOOREMPLOYEE_H

#include "FloorStaff.h"
#include<vector>
#include<string>

/**
 * @class FloorEmployee
 * @brief Regular employee handling on-floor customer queries.
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

#endif 