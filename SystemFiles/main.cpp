#include "PlantInventory.h"
#include "InventoryObserver.h"
#include "SalesFloorObserver.h"
#include "Staff.h"
#include "FloorStaff.h"
#include "SalesStaff.h"
#include "StaffFactory.h"
#include "ManagerFactory.h"
#include "EmployeeFactory.h"

#include <iostream>

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

    std::cout << std::endl;

    PlantInventory* greenhouse = new PlantInventory();
    std::cout << "Greenhouse inventory created." << std::endl << std::endl;

    std::cout << "Creating staff observers:" << std::endl << std::endl;
    InventoryObserver* floorManagerObserver = new InventoryObserver(f1);
    InventoryObserver* floorEmployeeObserver = new InventoryObserver(f2);
    SalesFloorObserver* salesManagerObserver = new SalesFloorObserver(s1);
    SalesFloorObserver* salesEmployeeObserver = new SalesFloorObserver(s2);

    greenhouse->attach(floorManagerObserver);
    greenhouse->attach(floorEmployeeObserver);
    greenhouse->attach(salesManagerObserver);
    greenhouse->attach(salesEmployeeObserver);

    greenhouse->displayInventory();

    std::cout << std::endl;
    std::cout << "Simulating inventory changes in the greenhouse." << std::endl << std::endl;
    std::cout << "Roses have matured and are ready for sale!" << std::endl;
    greenhouse->addPlant("Rose", 15);
    std::cout << "Oak trees have matured!" << std::endl;
    greenhouse->addPlant("Oak", 8);
    std::cout << "Another batch of Roses is ready!" << std::endl;
    greenhouse->addPlant("Rose", 10);

    greenhouse->displayInventory();

    salesManagerObserver->displaySalesFloor();

    std::cout << "Customer purchases 5 Roses" << std::endl;
    greenhouse->removePlant("Rose", 5);
    std::cout << std::endl;
    
    std::cout << "Customer purchases 3 Oaks" << std::endl;
    greenhouse->removePlant("Oak", 3);
    std::cout << std::endl;
    
    std::cout << "Large order: 18 Roses" << std::endl;
    greenhouse->removePlant("Rose", 18);
    
    greenhouse->displayInventory();

    std::cout << std::endl;

    std::cout << "Selling more Oaks to trigger low stock warning" << std::endl;
    greenhouse->removePlant("Oak", 4);
    
    std::cout << "Attempting to sell remaining Oak" << std::endl;
    greenhouse->removePlant("Oak", 1);
    
    greenhouse->displayInventory();

    std::cout << std::endl;

    greenhouse->detach(floorEmployeeObserver);

    std::cout << std::endl;

    greenhouse->addPlant("Tulip", 12);
    
    greenhouse->displayInventory();

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

    // Delete observers
    delete floorManagerObserver;
    delete floorEmployeeObserver;
    delete salesManagerObserver;
    delete salesEmployeeObserver;

    // Delete inventory
    delete greenhouse;

    return 0;
}