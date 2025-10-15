#ifndef STAFFFACTORY_H
#define STAFFFACTORY_H

#include "FloorStaff.h"

#include "SalesStaff.h"
#include <string>

class StaffFactory{
    public:
        StaffFactory();
        virtual ~StaffFactory();
        virtual FloorStaff* createFloorStaff(std::string name)=0;
        virtual SalesStaff* createSalesStaff(std::string name)=0;
};

#endif