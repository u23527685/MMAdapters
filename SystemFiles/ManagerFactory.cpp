#include "ManagerFactory.h"
#include "FloorManager.h"
#include "SalesManager.h"

using namespace std;

Managerfactory::Managerfactory() : StaffFactory() {}

Managerfactory::~Managerfactory() {}

FloorStaff *Managerfactory::createFloorStaff(std::string name)
{
    return new FloorManager(name);
}

SalesStaff *Managerfactory::createSalesStaff(std::string name)
{
    return new SalesManager(name);
}