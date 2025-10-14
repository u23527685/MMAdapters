#ifndef MANAGERFACTORY_H
#define MANAGERFACTORY_H

#include "StaffFactory.h"

class Managerfactory:public StaffFactory{
    public: 
        Managerfactory();
        ~Managerfactory();
        FloorStaff* createFloorStaff() override;
        SalesStaff* createSalesStaff() override;
};

#endif // !MANAGERFACTORY_H