/**
 * @file SalesStaff.h
 * @brief Abstract base class for sales department staff members
 */

#ifndef SALESSTAFF_H
#define SALESSTAFF_H

#include "Staff.h"

/**
 * @class SalesStaff
 * @brief Abstract base class for staff members in the sales department
 * 
 * Provides common functionality for sales staff including query handling
 * and response generation. Concrete classes must implement staffCanHandle()
 * to specify their responsibilities and reply() to handle queries.
 * 
 * @see Staff
 */
class SalesStaff : public Staff {
    public:
        /**
         * @brief Construct a sales staff member with given name
         * @param name The staff member's name
         */
        SalesStaff(std::string name);
        
        /**
         * @brief Virtual destructor
         */
        virtual ~SalesStaff();
        
        /**
         * @brief Handle an incoming query using chain of responsibility
         * @param query The query to handle (non-owning pointer)
         */
        void handleQuery(Query* query) override;
        
        /**
         * @brief Check if this staff member can handle a query type
         * @param type The query type to check
         * @return true if the staff member can handle it, false otherwise
         */
        virtual bool staffCanHandle(std::string type) = 0;
        
        /**
         * @brief Generate a reply for a query
         * @param query The query to reply to (non-owning pointer)
         */
        virtual void reply(Query* query) = 0;
};

#endif