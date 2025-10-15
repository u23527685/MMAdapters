#ifndef MANAGERFACTORY_H
#define MANAGERFACTORY_H

#include "StaffFactory.h"

class Managerfactory:public StaffFactory{
    public: 
        Managerfactory();
        ~Managerfactory();
        FloorStaff* createFloorStaff(std::string name) override;
        SalesStaff* createSalesStaff(std::string name) override;
};

#endif // !MANAGERFACTORY_H