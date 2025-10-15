#ifndef EMPLOYEEFACTORY_H
#define EMPLOYEEFACTORY_H

#include "StaffFactory.h"
#include<string>

class EmployeeFactory:public StaffFactory{
    public:
        EmployeeFactory();
        ~EmployeeFactory();
        FloorStaff* createFloorStaff(std::string name) override;
        SalesStaff* createSalesStaff(std::string name) override;
};

#endif // !EMPLOYEEFACTORY_H