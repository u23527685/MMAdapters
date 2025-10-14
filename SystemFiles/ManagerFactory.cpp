#include "ManagerFactory.h"
#include"FloorManager.h"
#include"SalesManager.h"

using namespace std;

Managerfactory::Managerfactory():StaffFactory(){}

Managerfactory::~Managerfactory(){}

FloorStaff* Managerfactory::createFloorStaff(){
    return new FloorManager();
}

SalesStaff* Managerfactory::createSalesStaff(){
    return new SalesManager();
}