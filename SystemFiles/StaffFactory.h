/**
 * @file StaffFactory.h
 * @brief Abstract factory for creating staff members.
 *
 * Defines an interface for factories to produce FloorStaff and
 * SalesStaff. Concrete factories implement creation methods
 * for employees or managers.
 *
 * @see FloorStaff
 * @see SalesStaff
 *
 */
#ifndef STAFFFACTORY_H
#define STAFFFACTORY_H

#include "FloorStaff.h"
#include "SalesStaff.h"
#include <string>

/**
 * @class StaffFactory
 * @brief Abstract base factory for creating different types of staff members
 *
 * This abstract factory defines the interface for creating floor and sales
 * staff members. Concrete factories implement these methods to create specific
 * staff types (employees or managers).
 */
class StaffFactory {
    public:
        /**
         * @brief Default constructor
         */
        StaffFactory();

        /**
         * @brief Virtual destructor
         */
        virtual ~StaffFactory();

        /**
         * @brief Create a floor staff member
         * @param name The name of the staff member to create
         * @return Pointer to the created FloorStaff (caller owns memory)
         */
        virtual FloorStaff* createFloorStaff(std::string name)=0;

        /**
         * @brief Create a sales staff member
         * @param name The name of the staff member to create
         * @return Pointer to the created SalesStaff (caller owns memory)
         */
        virtual SalesStaff* createSalesStaff(std::string name)=0;
};

#endif