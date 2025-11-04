/**
 * @file ManagerFactory.h
 * @brief Defines the factory for creating manager-level staff.
 *
 * The ManagerFactory is responsible for instantiating FloorManager and
 * SalesManager objects using the StaffFactory interface.
 *
 * @author 
 * Okaile Gaesale
 */
#ifndef MANAGERFACTORY_H
#define MANAGERFACTORY_H

#include "StaffFactory.h"

/**
 * @class ManagerFactory
 * @brief Factory for creating floor and sales managers.
 * @see StaffFactory
 */
class Managerfactory : public StaffFactory {
    public:
        /**
         * @brief Default constructor
         */
        Managerfactory();

        /**
         * @brief Virtual destructor
         */
        ~Managerfactory();

        /**
         * @brief Create a FloorManager instance
         * @param name The name of the manager to create
         * @return Pointer to new FloorManager (caller owns memory)
         */
        FloorStaff* createFloorStaff(std::string name) override;

        /**
         * @brief Create a SalesManager instance
         * @param name The name of the manager to create
         * @return Pointer to new SalesManager (caller owns memory)
         */
        SalesStaff* createSalesStaff(std::string name) override;
};

#endif