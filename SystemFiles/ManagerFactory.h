/**
 * @file ManagerFactory.h
 * @brief Concrete factory for creating managers
 */

#ifndef MANAGERFACTORY_H
#define MANAGERFACTORY_H

#include "StaffFactory.h"

/**
 * @class ManagerFactory
 * @brief Factory that creates floor and sales managers
 *
 * This concrete factory implements the StaffFactory interface to create
 * FloorManager and SalesManager instances.
 *
 * @see StaffFactory
 */
class Managerfactory : public StaffFactory
{
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
    FloorStaff *createFloorStaff(std::string name) override;

    /**
     * @brief Create a SalesManager instance
     * @param name The name of the manager to create
     * @return Pointer to new SalesManager (caller owns memory)
     */
    SalesStaff *createSalesStaff(std::string name) override;
};

#endif // !MANAGERFACTORY_H