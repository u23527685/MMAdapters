#ifndef EMPLOYEEFACTORY_H
#define EMPLOYEEFACTORY_H

#include "StaffFactory.h"

class EmployeeFactory:public StaffFactory{
    public:
        EmployeeFactory();
        ~EmployeeFactory();
        FloorStaff* createFloorStaff(std::string name) override;
        SalesStaff* createSalesStaff(std::string name) override;
};

#endif // !EMPLOYEEFACTORY_H