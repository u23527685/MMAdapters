#ifndef FLOORSTAFF_H
#define FLOORSTAFF_H

#include "Staff.h"
#include <string>

/**
 * @class FloorStaff
 * @brief Represents floor staff members who work on the operational floor.
 * 
 * @see Staff
 * @author Okaile
 * @version 1.0
 */
class FloorStaff : public Staff {
    public:
        FloorStaff(std::string name);
        virtual ~FloorStaff();
        void handleQuery() override;
        virtual bool staffCanHandle()=0;
        virtual void reply()=0;
};

#endif 