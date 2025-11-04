/**
 * @file FloorStaff.h
 * @brief Abstract base class for floor-level staff members.
 *
 * Serves as the base for FloorEmployee and FloorManager classes,
 * implementing shared behavior and chain-of-responsibility forwarding.
 *
 */
#ifndef FLOORSTAFF_H
#define FLOORSTAFF_H

#include "Staff.h"
#include <string>

/**
 * @class FloorStaff
 * @brief Base class for all floor staff types.
 */
class FloorStaff : public Staff {
    public:
        /**
         * @brief Construct a FloorStaff with the given name.
         * @param name Staff member's name.
         */
        FloorStaff(std::string name);

        /**
         * @brief Virtual destructor.
         */
        virtual ~FloorStaff();

        /**
         * @brief Entry point for handling a Query.
         *
         * This override logs receipt of the Query, prints its contents,
         * asks staffCanHandle() whether the current instance can service it,
         * calls reply() if it can, or forwards the Query to the next Staff
         * in the chain when it cannot be handled.
         *
         * @param query Pointer to the Query to handle (non-owning).
         */
        void handleQuery(Query* query) override;

        /**
         * @brief Determine whether this staff member can handle queries of the given type.
         *
         * Implementations should return true for supported Query types (e.g.
         * "INFO", "STOCK", "CARE ROUTINE") and false otherwise.
         *
         * @param type The Query type string.
         * @return true if this staff member can handle the type, false otherwise.
         */
        virtual bool staffCanHandle(std::string type)=0;

        /**
         * @brief Produce a reply for the provided Query.
         *
         * Called when staffCanHandle(query->getType()) returns true. Implementations
         * should output or otherwise process the Query and may forward it if
         * further escalation is required.
         *
         * @param query Pointer to the Query to reply to (non-owning).
         */
        virtual void reply(Query* query)=0;
};

#endif // FLOORSTAFF_H