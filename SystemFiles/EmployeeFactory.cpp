#include "EmployeeFactory.h"
#include "SalesEmployee.h"
#include "FloorEmployee.h"

#include<string>

EmployeeFactory::EmployeeFactory():StaffFactory(){}

EmployeeFactory::~EmployeeFactory(){}

FloorStaff* EmployeeFactory::createFloorStaff(std::string name){
    return new FloorEmployee(name);
}

SalesStaff* EmployeeFactory::createSalesStaff(std::string name){
    return new SalesEmployee(name);
}