/**
 * @file FloorManager.h
 * @brief Class representing the manager of floor operations.
 *
 * Handles advanced floor-related queries requiring managerial authority,
 * such as stock and inventory control.
 *
 * @author 
 * Okaile Gaesale
 */
#ifndef FLOORMANAGER_H
#define FLOORMANAGER_H

#include "FloorStaff.h" 
#include<vector>

/**
 * @class FloorManager
 * @brief Manages floor staff and handles high-level queries.
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