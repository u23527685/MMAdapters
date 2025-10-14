#ifndef STAFFFACTORY_H
#define STAFFFACTORY_H

#include "FloorStaff.h"

#include "SalesStaff.h"

class StaffFactory{
    public:
        StaffFactory();
        virtual ~StaffFactory();
        virtual FloorStaff* createFloorStaff()=0;
        virtual SalesStaff* createSalesStaff()=0;
};

#endif