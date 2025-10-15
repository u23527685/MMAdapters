#include "StaffFactory.h"
#include"ManagerFactory.h"
#include"EmployeeFactory.h"
#include "Staff.h"
#include "FloorStaff.h"
#include "SalesStaff.h"

#include<iostream>

int main() {
    StaffFactory**factories= new StaffFactory* [2];
    factories[0]=new Managerfactory();
    factories[1]=new EmployeeFactory();

    FloorStaff* f1=factories[0]->createFloorStaff("John smith manager");
    FloorStaff* f2= factories[1]->createFloorStaff("Kabelo employee");

    SalesStaff* s1=factories[0]->createSalesStaff("Kattie dobson manager");
    SalesStaff* s2=factories[1]->createSalesStaff("Tebogo employee");

    s2->setNext(s1);
    f1->setNext(s2);
    f2->setNext(f1);

    std::cout<<"Query 1 \n"<<std::endl;

    f1->handleQuery();

    std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<"<<std::endl;

    std::cout<<"Query 2 \n"<<std::endl;

    f1->handleQuery();

    std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<"<<std::endl;

    std::cout<<"Query 3 \n"<<std::endl;

    f1->handleQuery();

    std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<"<<std::endl;

    std::cout<<"Query 4 \n"<<std::endl;

    f1->handleQuery();

    std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<"<<std::endl;

    std::cout<<"Query 5 \n"<<std::endl;

    f1->handleQuery();

    std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<"<<std::endl;

    std::cout<<"Query 6 \n"<<std::endl;

    f1->handleQuery();

    std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<"<<std::endl;

    // Delete the Staff objects
    delete f1;
    delete f2;
    delete s1;
    delete s2;

    // Delete the Factories
    delete factories[0];
    delete factories[1];

    // Delete the array itself
    delete[] factories;

    return 0;
}