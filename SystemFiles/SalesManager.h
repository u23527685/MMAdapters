/**
 * @file SalesManager.h
 * @brief Defines the SalesManager class for the sales department.
 *
 * The SalesManager class handles escalated queries and has
 * authority for special deals and promotional decisions.
 *
 * @see SalesStaff
 * @see SalesEmployee
 *
 */
#ifndef SALESMANAGER_H
#define SALESMANAGER_H

#include "SalesStaff.h"
#include<vector>

/**
 * @class SalesManager
 * @brief Represents a manager in the sales department
 * 
 * Handles escalated sales queries and has additional authority
 * for special deals and events.
 * 
 * @see SalesStaff
 */
class SalesManager : public SalesStaff {
    private:
        std::vector<std::string> responsibilities; /**< List of query types this manager can handle */
    
    public:
        /**
         * @brief Construct a sales manager with given name
         * @param name The manager's name
         */
        SalesManager(std::string name);
        
        /**
         * @brief Virtual destructor
         */
        virtual ~SalesManager();
        
        bool staffCanHandle(std::string type) override;
        void reply(Query* query) override;
};

#endif