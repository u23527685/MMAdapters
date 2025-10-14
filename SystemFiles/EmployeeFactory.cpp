#include "EmployeeFactory.h"
#include "SalesEmployee.h"
#include "FloorEmployee.h"

EmployeeFactory::EmployeeFactory():StaffFactory(){}

EmployeeFactory::~EmployeeFactory(){}

FloorStaff* EmployeeFactory::createFloorStaff(){
    return new FloorEmployee();
}

SalesStaff* EmployeeFactory::createSalesStaff(){
    return new SalesEmployee();
}