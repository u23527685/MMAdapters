#ifndef FLOORSTAFF_H
#define FLOORSTAFF_H

#include "Staff.h"
#include <string>

/**
 * @class FloorStaff
 * @brief Represents floor staff members who work on the operational floor.
 * 
 * @see Staff
 * @author Okaile Gaesale 23527685
 * @version 1.0
 */
class FloorStaff : public Staff {
    public:
        FloorStaff(std::string name);
        virtual ~FloorStaff();
        void handleQuery(Query* query) override;
        virtual bool staffCanHandle(std::string type)=0;
        virtual void reply(Query* query)=0;
};

#endif 