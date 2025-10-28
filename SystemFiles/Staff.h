#ifndef STAFF_H
#define STAFF_H

#include<string>
#include "PLantLifeCycle.h"
#include "LifeCycleObserver.h"
#include "PlantCareRoutine.h"
#include <iostream>

class Staff: public LifeCycleObserver{
    private:
        Staff* next;
        std::string name;
        PlantCareRoutine* careRoutine;
    public:
        virtual void handleQuery()=0;
        Staff(std::string name);
        virtual ~Staff();
        std::string getName();
        void setNext(Staff* staff);
        Staff* getNext();
        void update(PlantLifeCycle* lifeCycle) override;
};

#endif