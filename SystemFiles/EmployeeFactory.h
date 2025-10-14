#ifndef EMPLOYEEFACTORY_H
#define EMPLOYEEFACTORY_H

#include "StaffFactory.h"

class EmployeeFactory:public StaffFactory{
    public:
        EmployeeFactory();
        ~EmployeeFactory();
        FloorStaff* createFloorStaff() override;
        SalesStaff* createSalesStaff() override;
};

#endif // !EMPLOYEEFACTORY_H