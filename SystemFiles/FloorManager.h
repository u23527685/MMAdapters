/**
 * @file FloorManager.h
 * @brief Floor department manager implementation
 */

#ifndef FLOORMANAGER_H
#define FLOORMANAGER_H

#include "FloorStaff.h" 
#include<vector>

/**
 * @class FloorManager
 * @brief Represents a manager of floor operations
 * 
 * Handles floor-related queries that require manager authority,
 * particularly inventory and stock-related matters.
 * 
 * @see FloorStaff
 */
class FloorManager : public FloorStaff {
    private:
        std::vector<std::string> responsibilities; /**< List of query types this manager can handle */
    
    public:
        /**
         * @brief Construct a floor manager with given name
         * @param name The manager's name
         */
        FloorManager(std::string name);
        
        /**
         * @brief Virtual destructor
         */
        virtual ~FloorManager();
        
        bool staffCanHandle(std::string type) override;
        void reply(Query* query) override;
};

#endif // !FLOORMANAGER_H